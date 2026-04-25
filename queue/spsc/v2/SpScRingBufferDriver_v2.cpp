#include <iostream>
#include <thread>

#include "SpScRingBuffer_v2.h"
#include "SpScRingBufferProducer_v2.h"
#include "SpScRingBufferConsumer_v2.h"

void producerTask(spsc::v2::Producer<int>& producer) {
    for (int i = 0; i < 1000; ++i) {
        while (!producer.tryPush(i)) {
            // Busy-wait or some backoff
        }
        std::cout << "Produced: " << i << "\n";
    }
}

void consumerTask(spsc::v2::Consumer<int>& consumer) {
    int item;
    for (int i = 0; i < 1000; ++i) {
        while (!consumer.tryPop(item)) {
            // Busy-wait or some backoff
        }
        std::cout << "Consumed: " << item << "\n";
    }
}

int main() {
    using Buffer = spsc::v2::SpScRingBuffer<int>;
    using Producer = spsc::v2::Producer<int>;
    using Consumer = spsc::v2::Consumer<int>;

    Buffer buffer;
    Producer producer(buffer);
    Consumer consumer(buffer);

    std::thread producerThread(producerTask, std::ref(producer));
    std::thread consumerThread(consumerTask, std::ref(consumer));

    producerThread.join();
    consumerThread.join();

    std::cout << "Finished processing with v2." << std::endl;

    return 0;
}