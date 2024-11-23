//
// Created by fanch on 11/21/2024.
//

#include "ThreadPool.h"


ThreadPool::ThreadPool(size_t numThreads) {
    stop = false;
    for (int i = 0; i < numThreads; i++) {
        thread newThread(&ThreadPool::WorkerThread, this);
        threads.push_back(std::move(newThread));
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    cv.notify_all();
    for (auto &thread : threads) {
        thread.join();
    }
}

void ThreadPool::WorkerThread() {
    while (!stop) {
        std::function<void()> job;
        std::unique_lock<std::mutex> lock(mutex);

        cv.wait(lock, [this] {return !jobs.empty() || stop;});

        if (stop || jobs.empty()) {
            return;
        }

        job = jobs.front();
        jobs.pop();
        lock.unlock();

        try {
            job();
        } catch (const std::exception &e) {
            std::cerr << "Thread pool caught an exception: " << e.what() << std::endl;
        }

    }

}

void ThreadPool::EnqueueJob(std::function<void()> job) {
    std::unique_lock<std::mutex> lock(mutex);

    jobs.push(job);

    cv.notify_one();
}


