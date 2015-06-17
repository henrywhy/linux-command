#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>

int do_ls(const char * dir_name, int show_status);

int main(int argc, char * argv[])
{	
	int i;
	if(argc == 1) {
		if(!do_ls(".", 0)) {
			printf("open . error\n");
		}//ls current directory, default
	} else if(strcmp(argv[1], "-l") == 0) {
		if(argc == 2) {
			if(!do_ls(".", 1)) {
				printf("open . error\n");
			}
		} else {
			for(i=2; i<argc; i++) {
				printf("%s:\n", argv[i]);
				if(!do_ls(argv[i], 1)) {
					printf("open %s error\n", argv[i]);
				}
				printf("\n");
			}
		}		
	} else {
		for(i=1; i<argc; i++) {
			printf("%s:\n",argv[i]);
			if(!do_ls(argv[i], 0)) {
				printf("open %s error\n", argv[i]);
			}
			printf("\n");
		}
	}
	
	return 0;
}

int do_ls(const char * dir_name, int show_status)
{
	DIR * dir;
	struct dirent * cur_entry;
	struct stat status;
	struct passwd * user_info;
	char buffer[512];
	dir = opendir(dir_name);
	if(dir == NULL) {
		return 0; // open dir error	
	} else {
		while(cur_entry = readdir(dir)) {
			if(cur_entry->d_name[0] == '.') {
				//pass . .. .*
				continue;
			}
			if(show_status == 0) {
				printf("%s\n", cur_entry->d_name);
			} else {
				//get file status
				strcpy(buffer, dir_name);
				strcat(buffer, "/");
				stat(strcat(buffer, cur_entry->d_name), &status);
				user_info = getpwuid(status.st_uid);
				printf("%d %s %d %s\n", status.st_nlink, user_info->pw_name, status.st_size, cur_entry->d_name);	
			}
		}
		closedir(dir);
		return 1;	
	}
}
