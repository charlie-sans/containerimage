#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sqlite3.h>
#include <ncurses.h>
#include <menu.h>
//http server
#define PORT 8080
#define MAX_CONNECTIONS 10
#define MAX_REQUEST_SIZE 1024
#define MAX_RESPONSE_SIZE 1024
#define MAX_HEADER_SIZE 1024
#define MAX_BODY_SIZE 1024
#define MAX_FILE_SIZE 1024
#define MAX_FILE_NAME_SIZE 1024
#define MAX_FILE_PATH_SIZE 1024


//sqlite
#define DB_NAME "test.db"
#define TABLE_NAME "test"
#define MAX_QUERY_SIZE 1024
#define MAX_QUERY_RESULT_SIZE 1024
#define MAX_QUERY_RESULT_ROW_SIZE 1024
#define MAX_QUERY_RESULT_COL_SIZE 1024

//ncurses
#define MAX_MENU_SIZE 1024
#define MAX_MENU_ITEM_SIZE 1024
#define MAX_MENU_ITEM_COUNT 1024
#define MAX_MENU_ITEM_NAME_SIZE 1024
#define MAX_MENU_ITEM_PRICE_SIZE 1024
#define MAX_MENU_ITEM_DESC_SIZE 1024
#define MAX_MENU_ITEM_IMG_SIZE 1024
#define MAX_MENU_ITEM_IMG_PATH_SIZE 1024
#define MAX_MENU_ITEM_IMG_NAME_SIZE 1024
#define MAX_MENU_ITEM_IMG_EXT_SIZE 1024
#define PORT 8080
#define BUFFER_SIZE 104857600
