#include "libft.h"

int main(int argc, char **argv)
{
	(void)argc;
	int fd1;
	int fd2;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[1], O_RDONLY);
	char *s1;
	char *s2;
	s1 = get_next_line(fd1);
	s2 = get_next_line(fd2);
	printf("s1: %s", s1);
	printf("s2: %s", s2);
	free(s1);
	free(s2);
	s1 = get_next_line(fd1);
	s2 = get_next_line(fd2);
	printf("s1: %s", s1);
	printf("s2: %s", s2);
	free(s1);
	free(s2);
	s1 = get_next_line(fd1);
	s2 = get_next_line(fd2);
	printf("s1: %s", s1);
	printf("s2: %s", s2);
	free(s1);
	free(s2);
}
