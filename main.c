#include "main.h"
#include "ncurses.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sqlite3.h>

// ncurses login prompt

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // open database
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }


    // read from the users table
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM users";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char password[100];

    char input[100];
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    mvprintw(yMax / 3, xMax / 2, "Welcome to the login prompt!");
    mvprintw(yMax / 2, xMax / 2, "Enter password: ");
    getstr(input);

    // check if the password is correct
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (strcmp(input, sqlite3_column_text(stmt, 1)) == 0) {
            mvprintw(yMax / 2 + 1, xMax / 2, "Password correct!");
            break;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);


    refresh();
    sleep(2);

    endwin();

    return 0;
}