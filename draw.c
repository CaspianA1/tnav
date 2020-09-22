#include <limits.h>

void draw_borders(int max_width, int file_count, int path_length) {
	for (int y = 0; y < file_count + 1; y++)
		mvprintw(y, max_width, "|");
	for (int x = max_width + 1; x < path_length + 1; x += 2)
		mvprintw(file_count, x, "_");

	for (int x = 0; x < max_width; x += 2)
		mvprintw(file_count, x, "_");

	mvprintw(file_count + 1, path_length, "|");
	mvprintw(file_count + 2, path_length, "|");

	for (int x = 0; x < path_length + 1; x += 2)
		mvprintw(file_count + 2, x, "_");

}

void draw_files(char** files, int file_index) {
	int last_y = 0, longest_str_length = 0;
	for (int i = 0; files[i] != NULL; i++) {
		char* file = files[i];

		{
		int file_len = strlen(file);
		if (file_len > longest_str_length)
			longest_str_length = file_len;
		}

		int color_pair;
		bool use_color = false;

		if (i == file_index) {
			color_pair = 2;
			use_color = true;
		}
		else if (!is_a_file(file)) {
			color_pair = 1;
			use_color = true;
		}

		if (use_color)
			attron(COLOR_PAIR(color_pair));

		mvprintw(i, 0, file);

		if (use_color)
			attroff(COLOR_PAIR(color_pair));

		last_y++;
	}

	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));

	attron(COLOR_PAIR(1));
	mvprintw(last_y + 1, 0, cwd);
	attroff(COLOR_PAIR(1));

	draw_borders(longest_str_length, last_y, strlen(cwd));
}
