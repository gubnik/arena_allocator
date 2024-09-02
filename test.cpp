#include "arena.hpp"
#include <cstdio>

int main (int argc, char *argv[])
{
  arena::allocator <int> lifetime_1 = arena::allocator<int>::create (40000000);
  int * A1 = lifetime_1.allocate(8000);
  int * A2 = lifetime_1.allocate(64000);
  for (int i = 0; i < 100; i++)
  {
    A1 [i] = i;
    A2 [i] = i;
  }
  for (int i = 0; i < 16; i++)
    printf("%d ", A1 [i]);
  putchar('\n');
  for (int i = 0; i < 16; i++)
    printf("%d ", A1 [i]);
  putchar('\n');
  printf("1 - %ul\n2 - %ul\n", A1, A2);
  return 0;
}
