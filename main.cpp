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

  //Some more flags
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISIG | IXON);
  raw.c_cflag |= (CS8);
  
  //Disable echo and canonical mode
   raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

   //Turing off all the output process
   raw.c_oflag &= ~(OPOST);


    //adding the time 
    raw.c_cc[VMIN] = 0 ;
    raw.c_cc[VTIME] = 1 ;

   //Apply new settings
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char* argv[]){
  enableRawMode();


  while(1){

    char c = '\0';
    std::cin.get(c);
  
    if(std::iscntrl(static_cast<unsigned char>(c))){
      
      printf("%d\r\n",static_cast<unsigned char>(c));

    }else{
      printf("%d('%c')\r\n",static_cast<unsigned char>(c),c);
    }

    if( c == 'q') break;

  }

  return 0;
}
