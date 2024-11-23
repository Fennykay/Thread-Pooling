#include <iostream>
#include <chrono>
#include "ThreadPool.h"

int main() {
    ThreadPool pool(4);  // Create pool with 4 threads

    // Test 1: CPU-bound tasks
    std::vector<int> results(10, 0);
    for (int i = 0; i < 10; i++) {
        pool.EnqueueJob([&results, i]() {
            // Simulate CPU-intensive work
            int sum = 0;
            for(int j = 0; j < 1000000; j++) {
                sum += j;
            }
            results[i] = sum;
        });
    }

    // Test 2: IO-bound tasks
    for (int i = 0; i < 5; i++) {
        pool.EnqueueJob([i]() {
            std::cout << "IO task " << i << " sleeping..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "IO task " << i << " finished!" << std::endl;
        });
    }

    // Give some time for tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Print results
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "Result " << i << ": " << results[i] << std::endl;
    }

    return 0;
}