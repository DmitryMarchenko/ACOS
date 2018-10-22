#pragma once
#include <iostream>
#include <limits>
#include <cassert>

template <typename T>
class MyStack {
public:
    MyStack();
    explicit MyStack(size_t start_size);
    ~MyStack();

    void Push(T value);
    T Pop();
    size_t Size();
    bool Empty();

private:
    bool ok();
    void dump();
    void assert_ok();
    size_t calc_check_sum();
    void gen_canaries();
    void constructor(size_t start_size);
    void resize();

    T* buffer;
    size_t buffer_size;
    size_t top;
    T canary_1_value, canary_2_value;
    size_t check_sum;
};

template <typename T>
MyStack<T>::MyStack() {
    constructor(8);
}

template <typename T>
MyStack<T>::MyStack(size_t start_size) {
    constructor(start_size);
}

template <typename T>
void MyStack<T>::constructor(size_t start_size) {
    buffer_size = start_size + 2;
    buffer = new T[buffer_size];
    top = 1;
    gen_canaries();
    check_sum = calc_check_sum();
}

template <typename T>
MyStack<T>::~MyStack() {
    delete[] buffer;
}

template <typename T>
void MyStack<T>::gen_canaries() {
    auto canary_1_ptr = (char*)(&canary_1_value);
    auto canary_2_ptr = (char*)(&canary_2_value);
    for (size_t i = 0; i < sizeof(T); ++i) {
        canary_1_ptr[i] = static_cast<char>(rand() % std::numeric_limits<char>::max());
        canary_2_ptr[i] = static_cast<char>(rand() % std::numeric_limits<char>::max());
    }
    buffer[0] = canary_1_value;
    buffer[buffer_size - 1] = canary_2_value;
}

template <typename T>
size_t MyStack<T>::calc_check_sum() {
    size_t result = 0;
    auto ptr = (char*)(buffer);
    for (size_t i = 0; i < buffer_size * sizeof(T); ++i) {
        result += (i + 1) * static_cast<size_t>(ptr[i]);
    }
    return result;
}

template <typename T>
bool MyStack<T>::ok() {
    return buffer[0] == canary_1_value
           && buffer[buffer_size - 1] == canary_2_value
           && calc_check_sum() == check_sum;
}

template <typename T>
size_t MyStack<T>::Size() {
    return top - 1;
}

template <typename T>
bool MyStack<T>::Empty() {
    return top == 1;
}

template <typename T>
void MyStack<T>::dump() {
    std::cout << "Stack [" << this << "] (" << ((ok())? "ok" : "error") << ") {" << std::endl;
    std::cout << "\tcanary 1 = " << &buffer[0] << "; ("
              << ((canary_1_value == buffer[0])? "ok" : "error") << ")" << std::endl;
    std::cout << "\tcanary 2 = " << &buffer[buffer_size - 1] << "; ("
              << ((canary_2_value == buffer[buffer_size - 1])? "ok" : "error") << ")" << std::endl;
    size_t check_sum_ = calc_check_sum();
    std::cout << "\tcheck sum = " << check_sum_ << "; ("
              << ((check_sum_ == check_sum)? "ok" : "error") << ")" << std::endl;
    std::cout << "\tdata[" << buffer_size - 2 << "] {";
    for (size_t i = 1; i < buffer_size - 1; ++i) {
        std::cout << std::endl << "\t\t[" << i - 1 << "]:" << buffer[i];
        if (i == top) {
            std::cout << " (POISON)";
        }
    }
    std::cout << std::endl << "\t}" << std::endl << "}" << std::endl;
}

template <typename T>
void MyStack<T>::assert_ok() {
    if (!ok()) {
        dump();
        std::cerr << "Stack invalid!" << std::endl;
        exit(123);
    }
}

template <typename T>
void MyStack<T>::Push(T value) {
    assert_ok();
    if (top == buffer_size - 2) {
        resize();
        assert_ok();
    }
    buffer[top] = value;
    ++top;
    check_sum = calc_check_sum();
    assert_ok();
}

template <typename T>
T MyStack<T>::Pop() {
    assert_ok();
    assert(!Empty());
    --top;
    assert_ok();
    return buffer[top];
}

template <typename T>
void MyStack<T>::resize() {
    T* old_buffer = buffer;
    buffer_size += buffer_size - 2;
    buffer = new T[buffer_size];
    gen_canaries();
    for (size_t i = 1; i < top; ++i) {
        buffer[i] = old_buffer[i];
    }
    check_sum = calc_check_sum();
    delete[] old_buffer;
}