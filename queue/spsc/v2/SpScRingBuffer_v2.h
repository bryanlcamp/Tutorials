#pragma once

#include <atomic>
#include <array>
#include <cstddef>
#include <chrono>

namespace spsc::v2 {

inline constexpr int DEFAULT_RING_BUFFER_CAPACITY = 1024;

template <typename T, size_t Capacity = DEFAULT_RING_BUFFER_CAPACITY>
class SpScRingBuffer {
public:
    SpScRingBuffer() noexcept
        : _head(0), _tail(0), _dropped(0), _highWaterMark(0) {}

    bool tryPush(const T& item) noexcept {
        size_t head = _head.load(std::memory_order_relaxed);
        size_t next = increment(head);
        if (next == _tail.load(std::memory_order_acquire)) {
            _dropped.fetch_add(1, std::memory_order_relaxed);
            return false;
        }

        _buffer[head] = item;
        _head.store(next, std::memory_order_release);
        updateHighWaterMark(next);
        return true;
    }

    bool push(const T& item, uint32_t timeoutMs = 5000) noexcept {
        auto startTime = std::chrono::steady_clock::now();
        while (true) {
            size_t head = _head.load(std::memory_order_relaxed);
            size_t next = increment(head);
            if (next != _tail.load(std::memory_order_acquire)) {
                _buffer[head] = item;
                _head.store(next, std::memory_order_release);
                updateHighWaterMark(next);
                return true;
            }

            // Timeout handling
            if (std::chrono::steady_clock::now() - startTime > std::chrono::milliseconds(timeoutMs)) {
                return false;
            }
        }
    }

    bool tryPop(T& item) noexcept {
        size_t tail = _tail.load(std::memory_order_relaxed);
        if (tail == _head.load(std::memory_order_acquire)) {
            return false;
        }

        item = _buffer[tail];
        _tail.store(increment(tail), std::memory_order_release);
        return true;
    }

private:
    std::array<T, Capacity> _buffer;
    alignas(64) std::atomic<size_t> _head;
    alignas(64) std::atomic<size_t> _tail;
    std::atomic<size_t> _dropped;
    std::atomic<size_t> _highWaterMark;

    size_t increment(size_t idx) const noexcept {
        return (idx + 1) & (Capacity - 1);
    }

    void updateHighWaterMark(size_t head) noexcept {
        size_t current = _highWaterMark.load(std::memory_order_relaxed);
        size_t used = (head + Capacity - _tail.load(std::memory_order_relaxed)) & (Capacity - 1);
        if (used > current) {
            _highWaterMark.store(used, std::memory_order_relaxed);
        }
    }
};

}  // namespace spsc::v2