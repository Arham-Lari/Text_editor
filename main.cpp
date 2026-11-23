#include <iostream>

int main(int argc, char* argv[]){

  char c;

  while(std::cin.get(c) && c != 'q'){

    std::cout<<"editor is working";

  }

  std::cout<<"the terminal is stopeed working";

  return 0;
}
