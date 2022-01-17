#ifndef B3_ATAPPEAL_HPP
#define B3_ATAPPEAL_HPP

#include <cstddef>

template <typename Container>
class AtAppeal {
public:
  static typename Container::reference getElement(Container &container, std::size_t index);
  static std::size_t getBegin(const Container&);
  static std::size_t getEnd(const Container &container);
  static std::size_t getNext(std::size_t index);
};

template <typename Container>
typename Container::reference AtAppeal<Container>::getElement(Container &container, std::size_t index)
{
  return container.at(index);
}

template <typename Container>
std::size_t AtAppeal<Container>::getBegin(const Container&)
{
  return 0;
}

template <typename Container>
std::size_t AtAppeal<Container>::getEnd(const Container &container)
{
  return container.size();
}

template <typename Container>
std::size_t AtAppeal<Container>::getNext(std::size_t index)
{
  return index + 1;
}

#endif //B3_ATAPPEAL_HPP
