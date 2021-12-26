# Simple C++ HTTP Web Server

This web server is developed and tested on Linux with below specifications:

  * OS: Ubuntu Desktop 20.04.1 LTS x86_64
  * Kernel: 5.11.11-051111-generic
  * CPU: AMD Ryzen 5 2500U @ 2.000GHz
  * Memory: 8 GB



## Features

  * HTTP GET method only
  * Serve a simple HTML file from `html/` directory
  * Handle 10k concurrent connections.
  * Serve 50k request per second.



## Available Page

  * `http://localhost:8080/`
  * `http://localhost:8080/about.html`
  * `http://localhost:8080/contacts/`
  * Unrecognize URL will display error page (`404.html`)



## Testing Phase

Tested using [wrk](https://github.com/wg/wrk), a modern HTTP benchmarking tool

```
> ./wrk -t4 -c10000 -d10s http://localhost:8080/

Running 10s test @ http://localhost:8080/
  4 threads and 10000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    10.04ms    6.86ms  38.53ms   67.92%
    Req/Sec    14.25k     0.96k   16.24k    72.70%
  564853 requests in 10.07s, 113.93MB read
  Socket errors: connect 8983, read 0, write 0, timeout 0
  Non-2xx or 3xx responses: 278627
Requests/sec:  56108.52
Transfer/sec:     11.32MB
```
