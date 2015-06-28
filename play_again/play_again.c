#include <stdio.h>

//0->yes  1->no
int get_response(const char * question);

int main(int argc, char * argv[])
{
	char question[] = "play again?";
	int response;
	response = get_response(question);
	return response;
}

int get_response(const char * question)
{
	printf("%s (y/n)", question);
	while(1) {
		switch(getchar()) {
			case 'y' :
			case 'Y' :
				return 0;
			case 'n' :
			case 'N' :
			case EOF :
				return 1;
		}
	}	
}
