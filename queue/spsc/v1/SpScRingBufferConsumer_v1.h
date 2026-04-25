#pragma once

#include "SpScRingBuffer_v1.h"

namespace spsc::v1 {

template <typename T, size_t Capacity = DEFAULT_RING_BUFFER_CAPACITY>
class Consumer {
public:
    explicit Consumer(SpScRingBuffer<T, Capacity>& buffer) noexcept
        : _buffer(buffer) {}

    bool tryPop(T& item) noexcept {
        return _buffer.tryPop(item);
    }

private:
    SpScRingBuffer<T, Capacity>& _buffer;
};

} // namespace spsc::v1