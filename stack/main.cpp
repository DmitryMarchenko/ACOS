#include <iostream>
#include "my_stack.h"

int main() {
    MyStack<int> s;
    for (int i = 5; i < 15; ++i) {
        s.Push(i);
        assert(s.Size() == i - 4);
    }
    for (int i = 0; i < 10; ++i) {
        assert(s.Pop() == 14 - i);
        assert(s.Size() == 9 - i);
    }
    assert(s.Empty());
    return 0;
}