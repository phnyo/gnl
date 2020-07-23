#include "get_next_line.h"
#include<limits.h>

int main(int argc, char **argv)
{
	int fd[argc - 1];
	int itr = 1;
	int flg;
	if (argc >= 2)
		while (itr < argc)
			fd[itr - 1] = open(argv[itr++], O_RDONLY);
	else
		fd[0] = -1;
	char *c = malloc(sizeof(char) * INT_MAX);
		flg = 1;
		itr = 1;
		while (itr < argc)
		{
			while(get_next_line(fd[itr], &c) == 1)
			//{
				printf("%s\n", c);
				/*while (get_next_line(fd[itr+1], &c) > 0)
					printf("%s", c);*/
			//}
			itr++;
		}
	free(c);
}