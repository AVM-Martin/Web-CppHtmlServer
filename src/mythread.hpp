#ifndef MYTHREAD_HPP
#define MYTHREAD_HPP

#include <queue>
#include <vector>

#include <pthread.h>

#include "mydata.hpp"


class mythread : private std::queue<request_data> {
    pthread_mutex_t worker_lock;
    pthread_cond_t worker_cond;

    std::vector<pthread_t> workers;
    int n_workers;

    static void* do_request(void* _obj);

public:
    void init(int _n_workers);
    void destroy();

    void queue_request(request_data data);
};

#endif
