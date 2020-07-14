#include "get_next_line.h"
#include<limits.h>

int main(int argc, char **argv)
{
	int fd;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = -1;
	char *c = malloc(sizeof(char) * INT_MAX);
	while (get_next_line(fd, &c) == 1)
		printf("%s", c);
    printf("%s", c);
	free(c);
}
