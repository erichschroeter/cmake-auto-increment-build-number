#include <stdio.h>

#include "version.h"

int main(int argc, char **argv)
{
	printf("version: %s\n", EXAMPLE_VERSION);

	printf("compiled: %s %s\n", EXAMPLE_COMPILE_DATE, EXAMPLE_COMPILE_TIME);
	printf("%s\n", hello_world());
	return 0;
}
