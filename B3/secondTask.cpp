#include <ostream>
#include <algorithm>
#include <iterator>

#include "container.hpp"

void executeSecondTask(std::ostream &out)
{
  Container container(1, 10);
  std::copy(container.begin(), container.end(), std::ostream_iterator<std::size_t>(out, " "));
  out << '\n';
  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<std::size_t>(out, " "));
  out << '\n';
}
