#include <iostream>
#include <thread>
#include <chrono>

#include "ring_buffer.h"
#include "producer.h"
#include "consumer.h"

int main() {
    // Create a ring buffer of integers with a capacity of 1024
    spsc::RingBuffer<int, 1024> buffer;

    // Create a producer that will push values to the buffer
    spsc::Producer<int, 1024> producer(buffer);

    // Create a consumer that will consume values from the buffer
    spsc::Consumer<int, 1024> consumer(
        buffer,
        [](int v) {
            std::cout << "Consumed: " << v << "\n";
        }
    );

    // Start the consumer thread
    consumer.start();

    // Producer pushes 10 items into the buffer
    for (int i = 0; i < 10; ++i) {
        while (!producer.push(i)) { // Block if buffer is full
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for a bit to prevent busy-waiting
        }
    }

    // Wait for consumer to finish processing
    consumer.stop();

    return 0;
}