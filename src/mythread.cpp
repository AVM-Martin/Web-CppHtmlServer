#include <csignal>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>

#include "myconstants.hpp"
#include "mydata.hpp"
#include "myparser.hpp"
#include "mythread.hpp"


void mythread::init(int _n_workers) {
    if (pthread_mutex_init(&worker_lock, NULL) != 0) {
        perror("threading failed");
        raise(EXIT_FAILURE);
    }
    pthread_cond_init(&worker_cond, NULL);

    n_workers = _n_workers;
    workers.resize(n_workers);

    for (int i = 0; i < n_workers; i++) {
        pthread_create(&workers[i], NULL, do_request, (void*)this);
    }
}


void mythread::destroy() {
    pthread_cond_destroy(&worker_cond);
    pthread_mutex_destroy(&worker_lock);
}


void mythread::queue_request(request_data data) {
    pthread_mutex_lock(&worker_lock);
    push(data);
    pthread_cond_signal(&worker_cond);
    pthread_mutex_unlock(&worker_lock);
}


void* mythread::do_request(void* _obj) {
    mythread* obj = (mythread*)_obj;

    pthread_detach(pthread_self());

    while (true) {
        pthread_mutex_lock(&(obj->worker_lock));

        while (obj->empty()) {
            pthread_cond_wait(&(obj->worker_cond), &(obj->worker_lock));
        }

        request_data current = obj->front();
        obj->pop();
        pthread_mutex_unlock(&(obj->worker_lock));

        myparser::parse_request(myconstants::ROOT, current);
        myparser::send_data(current);
        close(current.socket_id);
    }
}
