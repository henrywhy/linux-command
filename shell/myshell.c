#include <unistd.h>

int main()
{
	char *argv[] = {"ls","-l", "/home/why", NULL};
	execvp(argv[0], argv);
	return 0;
}
