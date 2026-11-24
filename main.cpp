#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>

struct  termios original;

void disableRawMode(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void enableRawMode(){
  struct termios raw;

  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &original);
  
  //execcuting disableRawMode
  std::atexit(disableRawMode);

  //copy original settings
  raw = original;

  //Disable echo and canonical mode
   raw.c_lflag &= ~(ECHO | ICANON | ISIG);

   //disabling termination with the help of ctrl+x and ctrl+q(given by defautl)
    raw.c_lflag &=~(IXON);

   //Apply new settings
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char* argv[]){
  enableRawMode();

  char c;

  while(std::cin.get(c) && c != 'q'){
  
    if(std::iscntrl(c)){
      
      printf("%d\n",c);

    }else{
      printf("%d('%c')\n",c,c);
    }

  }

  return 0;
}
