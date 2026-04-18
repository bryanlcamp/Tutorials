#pragma once

#include <atomic>
#include <array>

namespace spsc {

template <typename T, size_t Capacity>
class RingBuffer {
public:
    RingBuffer() : head_(0), tail_(0) {}

    bool push(const T& item) {
        size_t currentHead = head_.load(std::memory_order_relaxed);
        size_t nextHead = increment(currentHead);

        if (nextHead == tail_.load(std::memory_order_acquire)) {
            // Buffer is full
            return false;
        }

        buffer_[currentHead] = item;
        head_.store(nextHead, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t currentTail = tail_.load(std::memory_order_relaxed);
        if (currentTail == head_.load(std::memory_order_acquire)) {
            // Buffer is empty
            return false;
        }

        item = buffer_[currentTail];
        tail_.store(increment(currentTail), std::memory_order_release);
        return true;
    }

private:
    size_t increment(size_t idx) const noexcept {
        return (idx + 1) % Capacity;
    }

private:
    std::array<T, Capacity> buffer_;
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
};

}  // namespace spsc