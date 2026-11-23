#include <iostream>
#include <termios.h>
#include <unistd.h>

struct  termios original;

void enableRawMode(){
  struct termios raw;

  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &original);

  //copy original settings
  raw = original;
}

int main(int argc, char* argv[]){

  char c;

  while(std::cin.get(c) && c != 'q'){


  }

  return 0;
}
