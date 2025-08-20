#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios; //original termios

void disableRawMode()
{
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
    tcgetattr(STDERR_FILENO, &orig_termios);
    atexit(disableRawMode); //call the function when exit

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &raw);
}

int main()
{
    enableRawMode();
    
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
