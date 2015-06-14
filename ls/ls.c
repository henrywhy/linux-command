#include <stdio.h>
#include <dirent.h>

int do_ls(char * dir_name);

int main(int argc, char * argv[])
{	
	int i;
	if(argc == 1) {
		if(!do_ls(".")) {
			printf("open . error\n");
		}//ls current directory, default
	} else {
		for(i=1; i<argc; i++) {
			printf("%s:\n",argv[i]);
			if(!do_ls(argv[i])) {
				printf("open %s error\n", argv[i]);
			}
			printf("\n");
		}
	}
	
	return 0;
}

int do_ls(char * dir_name)
{
	DIR * dir;
	struct dirent * cur_entry;
	dir = opendir(dir_name);
	if(dir == NULL) {
		return 0; // open dir error	
	} else {
		while(cur_entry = readdir(dir)) {
			printf("%s\n", cur_entry->d_name);
		}
		return 1;	
	}
}
