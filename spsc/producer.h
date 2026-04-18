#pragma once

namespace spsc {

template <typename Buffer>
class Producer {
public:
    explicit Producer(Buffer& buffer)
        : buffer_(buffer) {}

    template <typename T>
    void push(const T& value) {
        buffer_.try_push(value);
    }

private:
    Buffer& buffer_;
};

} // namespace spsc