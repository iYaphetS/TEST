#include <stdio.h>

#include <string.h>

int main()
{

	char *s1 = "sb_show 3";
	char *s2 = "aBcD  3";
	if (!strncasecmp(s1,"sb_show ",8))
		printf("same\n");
	else
		printf("not same\n");

	return 0;

}
