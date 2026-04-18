#pragma once

#include "ring_buffer.h"

namespace spsc {

template <typename T, size_t Capacity>
class Producer {
public:
    explicit Producer(RingBuffer<T, Capacity>& buffer) : buffer_(buffer) {}

    bool push(const T& item) {
        return buffer_.push(item);
    }

private:
    RingBuffer<T, Capacity>& buffer_;
};

}  // namespace spsc