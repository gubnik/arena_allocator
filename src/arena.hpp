#pragma once

#include <cstddef>
#include <new>
#include <sys/mman.h>

namespace arena
{

constexpr std::size_t arch_size = sizeof(void*);

template<class T>
class allocator 
{
public:
  /*
   * Static method imitating the constructor
   * @param p_MaxSize Amount of memory available to the allocator
   */
  static allocator <T> create (std::size_t p_MaxSize)
  {
    return allocator<T>(p_MaxSize);
  }

  /*
   * Allocate a certain amount of memory
   * @param p_AllocSize Amount of memoty to allocate 
   */
  T * allocate (const std::size_t p_AllocSize)
  {
    std::size_t size = (p_AllocSize % arch_size) ? (p_AllocSize / arch_size + 1) * arch_size : p_AllocSize;
    T * naddr = m_Current + size;
    if (naddr > m_End)
    {
      return nullptr;
    }
    T * addr = m_Current;
    m_Current = naddr;
    return addr;
  }
  /*
   * Unmap the allocated memory
   */
  ~ allocator <T> ()
  {
    munmap(m_Buffer, m_MaxSize);
  }

private:
  /*
   * Constructor. Safely kept away from unwanted usage
   * @param p_MaxSize Amount of memory available to the allocator
   */
  allocator <T> (std::size_t p_MaxSize)
  : m_MaxSize(p_MaxSize)
  {
    /*
      * Make a syscall to Linux kernel to allocate memory
      * We demand it is allowed to be read and to be written to
      * It is also only visible to the process it was allocated from and is not bound to any file
      * It does not have any offset 
      */
    m_Buffer = (T *) mmap(nullptr, m_MaxSize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
    m_Current = m_Buffer;
    m_End = m_Buffer + p_MaxSize;
    if (m_Buffer == MAP_FAILED)
    {
      throw std::bad_alloc();
    }
  }

  /*
  * The amount of memory allocated
  */
  std::size_t m_MaxSize = 0;
  /*
  * Address of an allocated memory
  * For type safety, it is of type-pointer type
  */
  T * m_Buffer = nullptr;
  T * m_Current = nullptr;
  T * m_End = nullptr;
};

}
