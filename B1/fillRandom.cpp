#include "fillRandom.hpp"

#include <stdexcept>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(-1.0, 1.0);

void fillRandom(double *array, int size)
{
  if (array == nullptr) {
    throw std::invalid_argument("Array can't be nullptr");
  }
  if (size < 0) {
    throw std::invalid_argument("Array's size can't be negative");
  }
  for (int i = 0; i < size; ++i) {
    array[i] = dis(gen);
  }
}
