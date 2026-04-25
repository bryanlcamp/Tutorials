#pragma once
#pragma once

#include "SpScRingBuffer_v3.h"

namespace spsc::v3 {

template <typename T>
class Consumer {
public:
    explicit Consumer(SpScRingBuffer<T>& ringBuffer) : _buffer(ringBuffer) {}

    // Non-blocking pop, returns false if empty
    bool tryPop(T& item) noexcept {
        return _buffer.tryPop(item);
    }

private:
    SpScRingBuffer<T>& _buffer;
};

} // namespace spsc::v3