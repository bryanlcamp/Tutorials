#pragma once

#include <array>
#include <atomic>
#include <cstddef>

namespace spsc {

template <typename T, size_t Capacity>
class RingBuffer {
public:
    using value_type = T;

    bool try_push(const T& value) {
        auto head = head_.load(std::memory_order_relaxed);
        auto next = increment(head);

        if (next == tail_.load(std::memory_order_acquire)) {
            return false;
        }

        buffer_[head] = value;
        head_.store(next, std::memory_order_release);
        return true;
    }

    bool try_pop(T& value) {
        auto tail = tail_.load(std::memory_order_relaxed);

        if (tail == head_.load(std::memory_order_acquire)) {
            return false;
        }

        value = buffer_[tail];
        tail_.store(increment(tail), std::memory_order_release);
        return true;
    }

private:
    static constexpr size_t increment(size_t i) {
        return (i + 1) % Capacity;
    }

private:
    std::array<T, Capacity> buffer_{};

    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};
};

} // namespace spsc