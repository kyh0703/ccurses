#include <curses.h>
#include <stdio.h>

int main()
{
    initscr();
    cbreak();
    noecho();

    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

    for (;;)
    {
        int c = wgetch(stdscr);

        // Exit the program on new line fed
        if (c == '\n')
            break;

        char buffer[512];
        size_t max_size = sizeof(buffer);
        if (c == ERR)
        {
            snprintf(buffer, max_size, "Nothing happened.");
        }
        else if (c == KEY_MOUSE)
        {
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                snprintf(buffer, max_size, "Mouse at row=%d, column=%d bstate=0x%08lx",
                         event.y, event.x, event.bstate);
            }
            else
            {
                snprintf(buffer, max_size, "Got bad mouse event.");
            }
        }
        else
        {
            snprintf(buffer, max_size, "Pressed key %d (%s)", c, keyname(c));
        }

        move(0, 0);
        insertln();
        addstr(buffer);
        clrtoeol();
        move(0, 0);
    }
}