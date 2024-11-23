//
// Created by fanch on 11/21/2024.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H


#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <iostream>

using std::vector, std::queue, std::thread;

class ThreadPool {
    vector<thread> threads;
    queue<std::function<void()>> jobs;
    bool stop;
    std::mutex mutex;
    std::condition_variable cv;
public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();
    void EnqueueJob(std::function<void()> job);
private:
    void WorkerThread();

};

#endif //THREADPOOL_THREADPOOL_H
