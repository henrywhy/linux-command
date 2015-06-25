#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define SIZE 512

int main(int argc, char * argv[])
{
	ino_t cur_inode;
	ino_t parent_inode;
	char cur_dirname[SIZE] = ".";
	char path[SIZE]="", temp[SIZE];
	
	DIR * cur_dir;
	DIR * parent_dir;	

	struct dirent * temp_dirent;
	while(1) {
		cur_dir = opendir(cur_dirname);
		while(temp_dirent=readdir(cur_dir)) {
			if(strcmp(temp_dirent->d_name, ".") == 0) {
				cur_inode = temp_dirent->d_ino;
			}
			
			if(strcmp(temp_dirent->d_name, "..") == 0) {
				parent_inode = temp_dirent->d_ino;
			}
		}
		closedir(cur_dir);
		
		//maybe go to root, parent's inode equal to its inode
		if(parent_inode == cur_inode) {
			strcpy(temp, path);
			strcpy(path, "/");
			strcat(path, temp);
			break;
		}
	
		//get current directory name from parent directory
		strcpy(temp, cur_dirname);
		strcat(temp, "/..");		
		parent_dir = opendir(temp);
		while(temp_dirent=readdir(parent_dir)) {
			if(temp_dirent->d_ino == cur_inode) {
				strcpy(temp, path);
				strcpy(path, temp_dirent->d_name);
				strcat(path, "/");
				strcat(path, temp);
				break;
			}
		}
		closedir(parent_dir);
	
		strcat(cur_dirname, "/..");
	}
	
	path[strlen(path) - 1] = '\0';
	puts(path);
	return 0;
}
