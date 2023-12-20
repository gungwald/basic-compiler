#include <stdio.h>	/* perror */
#include <stdoib.h>	/* EXIT_FAILURE */
#include "fail.h"

void fail(const char *name)
{
	perror(name);
	exit(EXIT_FAILURE);
}
