#include "libft.h"

int main(int argc, char **argv)
{
	(void)argc;

	int fd = open(argv[1], O_RDONLY);
	char *s;
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
	s = get_next_line(fd);
	printf("s: %s\n", s);
	free(s);
}
