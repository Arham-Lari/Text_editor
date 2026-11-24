#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>

struct  termios original;

void die(const char *s){
  perror(s);
  exit(-1);
}

void disableRawMode(){
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1)die("tcsetattr");  
}


void enableRawMode(){
  struct termios raw;

  // Get current terminal settings
  if(tcgetattr(STDIN_FILENO, &original) == -1) die("tcsetattr");

  //execcuting disableRawMode
  std::atexit(disableRawMode);

  //copy original settings
  raw = original;

  //Some more flags
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISIG | IXON);
  raw.c_cflag |= (CS8);

  //Disable echo and canonical mode
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

  //Turing off all the output process
  raw.c_oflag &= ~(OPOST);


  //adding the time 
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  //Apply new settings
 if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int main(int argc, char* argv[]){
  enableRawMode();

  while(1){

    char c = '\0';
    std::cin.get(c);

    if(!(std::cin.get(c))  && errno != EAGAIN) die("read");

    if(std::iscntrl(c)){

      printf("%d\r\n",c);

    }else{
      printf("%d('%c')\r\n",c,c);
    }

    if( c == 'q') break;

  }

  return 0;
}
