#include <iostream>
#include <string>
#include <stdexcept>

void executeFirstTask(std::istream& in, std::ostream& out);
void executeSecondTask(std::istream& in, std::ostream& out);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid amount of arguments";
    return 1;
  }
  if ((!isdigit(argv[1][0])) || (argv[1][1] != '\0')) {
    std::cerr << "Invalid task number";
    return 1;
  }
  try {
    switch (std::stoi(argv[1])) {
    case 1:
      executeFirstTask(std::cin, std::cout);
      break;
    case 2:
      executeSecondTask(std::cin, std::cout);
      break;
    default:
      std::cerr << "Invalid task number";
      return 1;
    }
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  return 0;
}
