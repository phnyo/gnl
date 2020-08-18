#include "get_next_line.h"
#include<limits.h>

int	get_next_line(int fd, char **line);

int main(int argc, char **argv)
{
	int itr = 1;
	int flg;

	char *c = malloc(sizeof(char) * 10);
		flg = 1;
		itr = 1;
	int fd = open(argv[1], O_RDONLY);
		/*while (itr < argc)
		{*/
			while(get_next_line(fd, &c) == 1)
			//{
				printf("%s\n", c);
				/*while (get_next_line(fd[itr+1], &c) > 0)
					printf("%s", c);
			
			//}
			itr++;
		}*/
	/*get_next_line(open(argv[1], O_RDONLY), &c);	
	printf("%s\n", c);
	get_next_line(open(argv[1], O_RDONLY), &c);
	printf("%s\n", c);*/	
	free(c);
}