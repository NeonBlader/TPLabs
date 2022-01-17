#include <iostream>
#include <stdexcept>
#include <cstring>

void sortWithDifferentAccess(const char *direction, std::istream &in = std::cin, std::ostream &out = std::cout);
void readTextAndOut(const char *fileName);
void refactorVectorWithIters(std::istream &in = std::cin, std::ostream &out = std::cout);
void fillRandomAndSort(const char *direction, std::size_t vectorSize, std::ostream &out = std::cout);

void checkForSpace(const char *argument)
{
  for (int i = 0; argument[i] != '\0'; ++i) {
    if (argument[i] == ' ') {
      throw std::invalid_argument("Extra space in argument");
    }
  }
}

int main(int argc, char *argv[])
{
  if ((argc < 2) || (argc > 4)) {
    std::cerr << "Invalid amount of parameters";
    return 1;
  }
  try {
    checkForSpace(argv[1]);
    switch (std::atoi(argv[1])) {
    case 1:
      if (argc != 3) {
        std::cerr << "Invalid amount of parameters";
        return 1;
      }
      checkForSpace(argv[2]);
      sortWithDifferentAccess(argv[2]);
      break;
    case 2:
      if (argc != 3) {
        std::cerr << "Invalid amount of parameters";
        return 1;
      }
      readTextAndOut(argv[2]);
      break;
    case 3:
      if (argc != 2) {
        std::cerr << "Invalid amount of parameters";
        return 1;
      }
      refactorVectorWithIters();
      break;
    case 4:
      if (argc != 4) {
        std::cerr << "Invalid amount of parameters";
        return 1;
      }
      checkForSpace(argv[3]);
      fillRandomAndSort(argv[2], std::atoi(argv[3]));
      break;
    default:
      std::cerr << "Invalid task number";
      return 1;
    }
  } catch (const std::exception &exception) {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}
