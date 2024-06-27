
#include "main.h"
#include "ncurses.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sqlite3.h>

#define CHOICE_AMOUNT 5

void window(WINDOW *win)
{
    // create a menu
    char *choices[] = {"SSH-Chat", "Discord", "Option 3", "Option 4", "Exit"};
    int choice;
    int highlight = 0;
    while (1)
    {
        for (int i = 0; i < CHOICE_AMOUNT; i++)
        {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i + 1, 1, choices[i]);
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == CHOICE_AMOUNT)
                highlight = CHOICE_AMOUNT - 1;
            break;
        case 10:
            break;
        case KEY_BACKSPACE:
            break;

        default:
            break;
        }
    }
    if (choice == 10)
    { // If Enter key was pressed
        // The user's choice is in 'highlight'
        mvprintw(5, 5, "You chose: %s", choices[highlight]);
        refresh();
        // Here, you can add a switch or if-else statements to act based on the choice
        switch (highlight)
        {
        case 0:
            // hand off the user to the ssh-chat program on port 2022
            printf("Connecting to ssh-chat...\n");
            system("ssh -o HostKeyAlgorithms=ssh-rsa -o FingerprintHash=md5 -p 2022 localhost");

            break;
        case 1:
            // Action for Option 2
            break;
        case 2:
            // Action for Option 3
            break;
        case 3:
            // Action for Option 4
            break;
        case 4:
            // Action for Exit
            break;
        default:
            // Default action or error handling
            break;
        }
    }

    wrefresh(win);
    sleep(1);
    delwin(win);
}

void loginPrompt(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM users";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return;
    }

    char password[100];
    char username[100];
    char usrpass[100];
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    mvprintw(yMax / 2, xMax / 2, "Welcome to Charlie's login prompt!");
    mvprintw(yMax / 2 + 1, xMax / 2, "Username: ");
    getstr(username);
    mvprintw(yMax / 2 + 2, xMax / 2, "Password: ");
    getstr(usrpass);
    if (username[0] == '\0' || usrpass[0] == '\0')
    {
        mvprintw(yMax / 2 + 2, xMax / 2, "Login failed!");
        refresh();
        sleep(2);
        endwin();
        return;
    }
    else
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            if (strcmp(username, (char *)sqlite3_column_text(stmt, 1)) == 0)
            {
                strcpy(password, (char *)sqlite3_column_text(stmt, 2));
                if (strcmp(usrpass, password) == 0)
                {
                    mvprintw(yMax / 2 + 3, xMax / 2, "Login successful!");
                    refresh();
                    sleep(2);
                    WINDOW *win = newwin(CHOICE_AMOUNT + 2, 20, 1, 1);
                    window(win);
                    break;
                }
                else
                {
                    mvprintw(yMax / 2 + 3, xMax / 2, "Login failed!");
                    refresh();
                    sleep(2);
                    endwin();
                    return;
                }
            }
        }
    }

    sqlite3_finalize(stmt);
}

    


int main()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // open database
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    loginPrompt(db);

    sqlite3_close(db);

    refresh();
    sleep(2);

    endwin();

    return 0;
}
