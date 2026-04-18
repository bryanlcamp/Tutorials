#include <iostream>

#include "ring_buffer.h"
#include "producer.h"
#include "consumer.h"

int main() {
    spsc::RingBuffer<int, 1024> buffer;

    spsc::Producer producer(buffer);

    spsc::Consumer consumer(
        buffer,
        [](int v) {
            std::cout << "Consumed: " << v << "\n";
        }
    );

    consumer.start();

    for (int i = 0; i < 10; ++i) {
        producer.push(i);
    }

    consumer.stop();
}