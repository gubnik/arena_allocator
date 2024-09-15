#include "../src/arena.hpp" // after installing use <arena_allocator>
#include <iostream>

int main (int argc, char *argv[])
{
  /*
    * Create a new arena allocator with a size of 152
    * It will be automatically removed via destructor
    * All of the memory used in it will only be deleted with the arena itself
    */
  arena::allocator <int> lifetime_1 = arena::allocator<int>::create (152);
  
  /* Allocate an int buffer
    */
  int * A1 = lifetime_1.allocate(81);
  std::cout << "Try to allocate 81 bytes. Actually allocates 88 because of padding." << '\n';
  for (int i = 0; i < 81; i++) A1[i] = i;
  std::cout << "All 88 bytes were successfully accessed!" << "\n\n";
  
  /* Allocate another
    */
  int * A2 = lifetime_1.allocate(64);
  std::cout << "Try to allocate 64 bytes. Allocates exactly 64 bytes." << '\n';
  for (int i = 0; i < 64; i++) A2[i] = i;
  std::cout << "All 64 bytes were successfully accessed!" << '\n';
}
