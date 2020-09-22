#include <curses.h>
#include <string.h>
#include "get_files.c"
#include "draw.c"

char* select_file() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	use_default_colors();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_RED);

	bool running = true, skip_refresh = false;
	int file_index = 0;

	while (running) {
		char** files = ls();
		int fc = get_file_count() - 1;

		switch (getch()) {
			case KEY_UP:
				file_index--;
				break;
			case KEY_DOWN:
				file_index++;
				break;
			case KEY_RIGHT: {
				clear();
				skip_refresh = true;
				chdir(files[file_index]);
				break;
			}
			case 10: { // KEY_ENTER
				endwin();
				char* file = files[file_index];
				char cwd[PATH_MAX];
				getcwd(cwd, sizeof(cwd));
				char path[strlen(file) + PATH_MAX + 1];
				strcpy(path, cwd);
				strcat(path, "/");
				strcat(path, file);
				char* heap_path = calloc(strlen(path), sizeof(char));
				strcpy(heap_path, path);
				return heap_path;
			}
		}

		if (skip_refresh) {
			skip_refresh = false;
			continue;
		}

		if (file_index + 1 > fc)
			file_index = fc - 1;
		else if (file_index < 0)
			file_index = 0;

		draw_files(files, file_index);
		free(files);
		refresh();
		napms(20); // excessive num of ticks otherwise
	}
	return ""; // to avoid warning
}


int main() {
	char* file = select_file();

	printf("File: %s\n", file);

	free(file);
}