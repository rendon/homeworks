#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <vector>


using namespace std;
const int MAX_WIDTH = 80;
const int MAX_HEIGHT = 40;
const int DOWN  = 8;
const int LEFT  = 6;
const int UP    = 10;
const int RIGHT = 12;
const int CONTINUE = 0;
const int DELAY = 500 * 1000; // microseconds

vector< pair<int, int> > snake;
bool M[MAX_HEIGHT+5][MAX_WIDTH+5];
int current_direction;

void move(int command)
{
  int i, size = snake.size();

  for (i = size - 1; i > 0; i--) {
    snake[i].first = snake[i-1].first;
    snake[i].second = snake[i-1].second;
  }


  if (command == CONTINUE) {
    switch (current_direction) {
      case UP:
        snake[0].first--;
        break;
      case RIGHT:
        snake[0].second++;
        break;
      case DOWN:
        snake[0].first++;
        break;
      case LEFT:
        snake[0].second--;
        break;
    };

  } else {
    switch (current_direction) {
      case UP:
        if (command == LEFT) {
          snake[0].second--;
          current_direction = LEFT;
        } else if (command == RIGHT) {
          snake[0].second++;
          current_direction = RIGHT;
        }
        break;

      case RIGHT:
        if (command == UP) {
          snake[0].first--;
          current_direction = UP;
        } else if (command == DOWN) {
          snake[0].first++;
          current_direction = DOWN;
        }
        break;

      case DOWN:
        if (command == LEFT) {
          snake[0].second--;
          current_direction = LEFT;
        } else if (command == RIGHT) {
          snake[0].second++;
          current_direction = RIGHT;
        }
        break;

      case LEFT:
        if (command == UP) {
          snake[0].first--;
          current_direction = UP;
        } else if (command == DOWN) {
          snake[0].first++;
          current_direction = DOWN;
        }
        break;
    };

  }
}

bool contains(const pair<int, int> &point)
{
  for (int i = 0; i < int(snake.size()); i++)
    if (point.first == snake[i].first && point.second == snake[i].second)
      return true;

  return false;
}


int main(int argc, char** argv)
{
  struct termios tio;
  int tty_fd, command, i, last_r, last_c, star_r, star_c;
  char v, ch;
  char *device = "/dev/ttyUSB0";

  srand(time(0));

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

  tcsetattr(tty_fd,TCSANOW,&tio);


  command = CONTINUE;
  current_direction = RIGHT;
  snake.push_back(make_pair(MAX_HEIGHT/2, 1));
  star_r = rand()%MAX_HEIGHT + 1;
  star_c = rand()%MAX_WIDTH + 1;
  M[star_r][star_c] = true;

  initscr();
  while (true) {
    int size = snake.size();
    last_r = snake[size-1].first;
    last_c = snake[size-1].second;

    for (i = 0; i < 50; i++) {
      command = 0;
      while (read(tty_fd, &v, 1) > 0) {
        if (v == '\n') break;
        if (v >= '0' && v <= '9')
          command = command * 10 + v - '0';
      }
      if (command != CONTINUE)
        break;
    }

    move(command);

    int r = snake[0].first;
    int c = snake[0].second;

    if (r < 1 || r > MAX_HEIGHT || c < 1 || c > MAX_WIDTH)  {
      move(MAX_HEIGHT/2, MAX_WIDTH/2 - 5);

      char signal = '1';
      write(tty_fd, &signal, 1);

      printw("GAME OVER");
      refresh();
      getch();

      break;
    } else {
      clear();
      if (M[r][c]) {
        M[r][c] = false;
        snake.push_back(make_pair(last_r, last_c));
        pair<int, int> point(rand()%MAX_HEIGHT + 1, rand()%MAX_WIDTH + 1);
        while (contains(point))
          point = make_pair(rand()%MAX_HEIGHT + 1, rand()%MAX_WIDTH + 1);

        M[point.first][point.second] = true;
        star_r = point.first;
        star_c = point.second;
      }

      for (i = 0; i <= MAX_WIDTH + 1; i++) {
        move(0, i);
        printw(".");
        move(MAX_HEIGHT + 1, i);
        printw(".");

      }

      for (i = 0; i <= MAX_HEIGHT + 1; i++) {
        move(i, 0);
        printw(".");
        move(i, MAX_WIDTH + 1);
        printw(".");
      }

      move(star_r, star_c);
      printw("*");

      for (i = 0; i < size; i++) {
        move(snake[i].first, snake[i].second);
        printw("#");
      }

      refresh();
    }

    command = 0;
    usleep(130000);
  }

  endwin();
  close(tty_fd);

  return EXIT_SUCCESS;
}

