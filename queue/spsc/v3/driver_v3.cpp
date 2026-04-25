#include <iostream>
#include <thread>
#include <vector>
#include "SpScRingBuffer_v3.h"
#include "SpScRingBuffer_Producer_v3.h"
#include "SpScRingBuffer_Consumer_v3.h"

constexpr size_t BUFFER_CAPACITY = 1024;

int main() {
    spsc::v3::SpScRingBuffer<int, BUFFER_CAPACITY> buffer;

    // Create producer and consumer
    spsc::v3::Producer<int> producer(buffer);
    spsc::v3::Consumer<int> consumer(buffer);

    // Consumer thread to pop items from the buffer
    std::thread consumerThread([&]() {
        int item;
        for (int i = 0; i < 10; ++i) {
            while (!consumer.tryPop(item)) {
                // If the buffer is empty, spin until we can pop
            }
            std::cout << "Consumed: " << item << std::endl;
        }
    });

    // Producer thread to push items to the buffer
    std::thread producerThread([&]() {
        for (int i = 0; i < 10; ++i) {
            while (!producer.tryPush(i)) {
                // If the buffer is full, spin until we can push
            }
            std::cout << "Produced: " << i << std::endl;
        }
    });

    // Wait for both threads to finish
    producerThread.join();
    consumerThread.join();

    return 0;
}