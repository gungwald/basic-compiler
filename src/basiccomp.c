#include <stdio.h>

#define MAX_PATH_LEN 64

char basic_file_name[MAX_PATH_LEN+1];
char assembly_file_name[MAX_PATH_LEN+1];

FILE *basic_file;
FILE *assembly_file;

void main(int arg_count, char *args[])
{
	switch (arg_count) {
		case 3:
			basic_file_name = args[1];
			assembly_file_name = args[2];
			break;
		case 2:
			basic_file_name = args[1];
			assembly_file_name = ask_user("ASSEMBLY OUTPUT FILE:");
			break;
		default:
			basic_file_name = ask_user("BASIC INPUT FILE");
			assembly_file_name = ask_user("ASSEMBLY OUTPUT FILE:");
			break;
	}

}

