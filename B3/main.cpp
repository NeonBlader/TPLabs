#include <iostream>
#include <cctype>
#include <stdexcept>

void executeFirstTask(std::istream& in, std::ostream& out);
void executeSecondTask(std::ostream& out);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid count of parameters\n";
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
      executeSecondTask(std::cout);
      break;
    default:
      std::cerr << "Invalid task number\n";
      return 1;
    }
  }
  catch (const std::exception &exception) {
    std::cerr << exception.what() << '\n';
    return 2;
  }
  return 0;
}
