#ifndef B3_ITERAPPEAL_HPP
#define B3_ITERAPPEAL_HPP

template <typename Container>
class IterAppeal {
public:
  static typename Container::reference getElement(Container&, typename Container::iterator ref);
  static typename Container::iterator getBegin(Container &container);
  static typename Container::iterator getEnd(Container &container);
  static typename Container::iterator getNext(typename Container::iterator ref);
};

template <typename Container>
typename Container::reference
IterAppeal<Container>::getElement(Container&, typename Container::iterator ref)
{
  return *ref;
}

template <typename Container>
typename Container::iterator IterAppeal<Container>::getBegin(Container &container)
{
  return container.begin();
}

template <typename Container>
typename Container::iterator IterAppeal<Container>::getEnd(Container &container)
{
  return container.end();
}

template <typename Container>
typename Container::iterator IterAppeal<Container>::getNext(typename Container::iterator ref)
{
  return ref++;
}

#endif //B3_ITERAPPEAL_HPP
