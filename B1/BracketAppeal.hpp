#ifndef B3_BRACKETAPPEAL_HPP
#define B3_BRACKETAPPEAL_HPP

#include <cstddef>

template <typename Container>
class BracketAppeal {
public:
  static typename Container::reference getElement(Container &container, std::size_t index);
  static std::size_t getBegin(const Container&);
  static std::size_t getEnd(const Container &container);
  static std::size_t getNext(std::size_t ref);
};

template <typename Container>
typename Container::reference BracketAppeal<Container>::getElement(Container &container, std::size_t index)
{
  return container[index];
}

template <typename Container>
std::size_t BracketAppeal<Container>::getBegin(const Container&)
{
  return 0;
}

template <typename Container>
std::size_t BracketAppeal<Container>::getEnd(const Container &container)
{
  return container.size();
}

template <typename Container>
std::size_t BracketAppeal<Container>::getNext(std::size_t ref)
{
  return ref + 1;
}

#endif //B3_BRACKETAPPEAL_HPP
