#pragma once

#include "SpScRingBuffer_v3.h"

namespace spsc::v3 {

template <typename T>
class Producer {
public:
    explicit Producer(SpScRingBuffer<T>& ringBuffer) : _buffer(ringBuffer) {}

    // Non-blocking push, returns false if full
    bool tryPush(const T& item) noexcept {
        return _buffer.tryPush(item);
    }

private:
    SpScRingBuffer<T>& _buffer;
};

} // namespace spsc::v3