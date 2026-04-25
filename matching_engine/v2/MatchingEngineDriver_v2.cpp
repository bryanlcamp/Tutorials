#include <iostream>
#include <thread>


void producerTask(spsc::v1::Producer<int>& producer) {
    for (int i = 0; i < 1000; ++i) {
        while (!producer.tryPush(i)) {
            // Busy-wait or some backoff
        }
        std::cout << "Produced: " << i << "\n";
    }
}

void consumerTask(spsc::v1::Consumer<int>& consumer) {
    int item;
    for (int i = 0; i < 1000; ++i) {
        while (!consumer.tryPop(item)) {
            // Busy-wait or some backoff
        }
        std::cout << "Consumed: " << item << "\n";
    }
}

int main() {

    using Buffer = spsc::v1::SpScRingBuffer<int>;
    using Producer = spsc::v1::Producer<int>;
    using Consumer = spsc::v1::Consumer<int>;

    Buffer buffer;
    Producer producer(buffer);
    Consumer consumer(buffer);

    std::thread producerThread(producerTask, std::ref(producer));
    std::thread consumerThread(consumerTask, std::ref(consumer));

    producerThread.join();
    consumerThread.join();

    std::cout << "Finished processing with v1." << std::endl;

    return 0;
}