# Arena allocator

A very simple C++ arena allocator using POSIX mmap.
It is unfit for commercial usage and should be only used for
educational purposes.

## Example
```c++
#include <arena_allocator>

int main (int argc, char ** argv)
{
    arena::allocator<int> Lifetime = arena::allocator<int>::create(400);
    int * Buf_1 = Lifetime.allocate(120);
    int * Buf_2 = Lifetime.allocate(80);
    int * Buf_3 = Lifetime.allocate(200);
    // Further allocation will yield null as arena's memory is over
    // Arena's memory is deallocated when it goes out of scope
}
```
