#pragma once

#include <thread>
#include <functional>
#include <atomic>
#include "ring_buffer.h"

namespace spsc {

template <typename T, size_t Capacity>
class Consumer {
public:
    using Callback = std::function<void(T)>;

    Consumer(RingBuffer<T, Capacity>& buffer, Callback callback)
        : buffer_(buffer), callback_(std::move(callback)), stopFlag_(false) {}

    void start() {
        stopFlag_ = false;
        thread_ = std::thread([this] { consumeLoop(); });
    }

    void stop() {
        stopFlag_ = true;
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    void consumeLoop() {
        T item;
        while (!stopFlag_) {
            if (buffer_.pop(item)) {
                callback_(item);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Sleep to prevent busy-waiting
            }
        }
    }

private:
    RingBuffer<T, Capacity>& buffer_;
    Callback callback_;
    std::atomic<bool> stopFlag_;
    std::thread thread_;
};

}  // namespace spsc