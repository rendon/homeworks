#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, char** argv)
{
  char buffer[50];
  struct termios tio;
  int tty_fd, volumen, i;
  char v, ch[2];
  char *device = "/dev/ttyUSB0";

  memset(&tio,0,sizeof(tio));
  tio.c_iflag=0;
  tio.c_oflag=0;
  tio.c_cflag=CS8|CREAD|CLOCAL;
  tio.c_lflag=0;
  tio.c_cc[VMIN]=1;
  tio.c_cc[VTIME]=5;

  
  tty_fd=open(device, O_RDWR | O_NONBLOCK);      
  cfsetospeed(&tio,B9600);
  cfsetispeed(&tio,B9600);

  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  tcsetattr(tty_fd,TCSANOW,&tio);
  volumen = 0;

  initscr();
  while (ch[0] !='q')
  {
    read(STDIN_FILENO, ch, 1);
    if (read(tty_fd,&v,1) > 0) {
      if (v == '\n') {
        sprintf(buffer, "amixer --quiet set Master %d%%", volumen);
        system(buffer);
        
        printw("[");
        for (i = 0; i < 100; i++) {
          if (i < volumen)
            printw("#");
          else
            printw(".");
        }
        printw("] %d%%", volumen);

        refresh();
        clear();

        volumen = 0;
      } else {
        if (v >= '0' && v <= '9')
          volumen = volumen * 10 + (v - '0');
      }
    }
  }

  endwin();
  close(tty_fd);
  
  return EXIT_SUCCESS;
}

