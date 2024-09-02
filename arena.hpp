#pragma once

#include <cstddef>
#include <sys/mman.h>


namespace arena
{

constexpr std::size_t arch_size = sizeof(void*);

template<class T>
class allocator 
{
public:
  static allocator <T> create (std::size_t p_MaxSize)
  {
    return allocator<T>(p_MaxSize);
  }

  T * allocate (const std::size_t p_AllocSize)
  {
    T * retAddr = &m_Buffer [m_Offset];
    m_Offset += arch_size * (p_AllocSize / arch_size + 1);
    return retAddr;
  }

  ~ allocator <T> ()
  {
  }

private:
  allocator <T> (std::size_t p_MaxSize)
  {
    m_MaxSize = p_MaxSize;
    m_Buffer = (T *) mmap(nullptr, m_MaxSize, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
  }

  std::size_t m_MaxSize = 0;
  std::size_t m_Offset = 0;
  T * m_Buffer = nullptr;

};
}
