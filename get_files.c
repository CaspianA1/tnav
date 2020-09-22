#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int is_a_file(char* current_file) {
	struct stat path_stat;
	stat(current_file, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

int get_file_count() {
	struct dirent* direc_entry;	
	DIR *cwd = opendir(".");

	int directory_count = 0;
	while ((direc_entry = readdir(cwd)) != NULL)
		directory_count++;
	closedir(cwd);
	return directory_count;
}

char** ls() {
	struct dirent* directory_entry;
	DIR *cwd = opendir(".");

	char** files = calloc(get_file_count() - 1, sizeof(char*) + sizeof(NULL));

	readdir(cwd); // get rid of .

	int ind = 0;
	while ((directory_entry = readdir(cwd)) != NULL)
		files[ind++] = directory_entry -> d_name;
	files[++ind] = NULL;

	closedir(cwd);

	return files;
}