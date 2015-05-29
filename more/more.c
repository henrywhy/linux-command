#include <stdio.h>

#define LENGTH 512

void do_more(FILE * fp);

int main(int argc, char *argv[])
{
	FILE * fp;
	int i;
	if(argc == 1) {
		do_more(stdin);
	} else {
		for(i=1; i<argc; ++i) {
			fp = fopen(argv[i], "r");
			do_more(fp);
			fclose(fp);
		}
	}
}

void do_more(FILE * fp) 
{
	char line[LENGTH];
	while(fgets(line, LENGTH, fp)) {
		fputs(line, stdout);
	}
}
