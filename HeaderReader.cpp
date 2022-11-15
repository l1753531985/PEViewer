#include <stdio.h>
#include <fstream>
#include "HeaderParser.h"

int main(int ac, char* argv[])
{
	if (ac < 2)
	{
		printf("fatal: there is no input file!");
		return -1;
	}
	HeaderParser header = HeaderParser(argv[ac-1]);
	return 0;
}
