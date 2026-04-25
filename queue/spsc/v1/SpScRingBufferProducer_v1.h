#pragma once

#include "SpScRingBuffer_v1.h"

namespace spsc::v1 {

template <typename T, size_t Capacity = DEFAULT_RING_BUFFER_CAPACITY>
class Producer {
public:
    explicit Producer(SpScRingBuffer<T, Capacity>& buffer) noexcept
        : _buffer(buffer) {}

    bool tryPush(const T& item) noexcept {
        return _buffer.tryPush(item);
    }

    bool push(const T& item, uint32_t timeoutMs = 5000) noexcept {
        return _buffer.push(item, timeoutMs);
    }

private:
    SpScRingBuffer<T, Capacity>& _buffer;
};

} // namespace spsc::v1