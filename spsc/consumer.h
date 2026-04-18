#pragma once

#include <atomic>
#include <thread>
#include <utility>
#include <thread>

namespace spsc {

template <typename Buffer, typename Callback>
class Consumer {
public:
    Consumer(Buffer& buffer, Callback cb)
        : buffer_(buffer),
          callback_(std::move(cb)),
          stop_(false) {}

    void start() {
        thread_ = std::thread([this] { run(); });
    }

    void stop() {
        stop_.store(true, std::memory_order_relaxed);
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    void run() {
        typename Buffer::value_type value;

        while (!stop_.load(std::memory_order_relaxed)) {
            if (buffer_.try_pop(value)) {
                callback_(value);
            } else {
                std::this_thread::yield();
            }
        }
    }

private:
    Buffer& buffer_;
    Callback callback_;
    std::atomic<bool> stop_;
    std::thread thread_;
};

} // namespace spsc