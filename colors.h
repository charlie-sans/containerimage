// terminal colors

#ifndef COLORS_H
#define COLORS_H

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#endif

void print_color(char *color, char *string) {
	printf("%s%s%s", color, string, RESET);
}

void clear_screen() {
	printf("\033[H\033[J");
}

void print_centered(char *string) {
	int length = strlen(string);
	int spaces = (80 - length) / 2;
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	printf("%s\n", string);
}

void print_centered_color(char *color, char *string) {
	int length = strlen(string);
	int spaces = (80 - length) / 2;
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	print_color(color, string);
	printf("\n");
}

void print_centered_color_bold(char *color, char *string) {
	int length = strlen(string);
	int spaces = (80 - length) / 2;
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	printf("\033[1m");
	print_color(color, string);
	printf("\033[0m\n");
}

void print_centered_bold(char *string) {
	int length = strlen(string);
	int spaces = (80 - length) / 2;
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	printf("\033[1m%s\033[0m\n", string);
}

void print_offset(char *string, int offset) {
	for (int i = 0; i < offset; i++) {
		printf(" ");
	}
	printf("%s\n", string);
}
void print_location(char *string, int x, int y) {
	printf("\033[%d;%dH%s", y, x, string);
}