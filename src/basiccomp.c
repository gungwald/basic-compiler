#include <stdio.h>
#include <stdlib.h>  /* atexit */
#include <stdbool.h> /* true, false */
#include <string.h>
#include <ctype.h>   /* isspace */

#include <apple2.h>  /* apple2_filetype.h: PRODOS_T_TXT, etc */

#include "applesoft.h"

#define STRING_CAPACITY 128

enum CompletionStatus {SUCCESS=0, FAILURE=1};
char basicfilename[STRING_CAPACITY];
char asmfilename[STRING_CAPACITY];

FILE *basicfile = NULL;
FILE *asmfile = NULL;

void finally(void);
void ask_user(const char *prompt, char answer[], size_t answer_size);
FILE *openbasfile(const char *name);
FILE *openasmfile(const char *name);
FILE *openbinfile(const char *name);
FILE *openfile(const char *file_name, const char *mode);
void rtrim(char s[]);
void compile(FILE *basicfile, FILE *asmfile);
char *buildasmname(char *asmname, char *basname, size_t size);

void main()
{
	if (atexit(finally) == FAILURE) {
		perror("atexit");
		exit(1);
	}
	ask_user("FILE:", basicfilename, sizeof(basicfilename));
	basicfile = openbasfile(basicfilename);
	buildasmname(asmfilename, basicfilename, sizeof(asmfilename));
	asmfile = openasmfile(asmfilename);
	compile(basicfile, asmfile);
	fclose(basicfile);
	fclose(asmfile);
}

void finally(void)
{
	if (basicfile != NULL)
		fclose(basicfile);
	if (asmfile != NULL)
		fclose(asmfile);
}

void ask_user(const char *prompt, /* modifies */ char answer[], size_t answer_size)
{
	//printf("sizeof(answer)=%d\r", answer_size);
	while (true) {
		printf("%s", prompt);
		fgets(answer, answer_size, stdin);
		rtrim(answer);
		if (strlen(answer) > 0)
			break;
		puts("Press Ctrl-Reset to abort.");
	}
}

FILE *openbasfile(const char *name) 
{
	_filetype = PRODOS_T_BAS;
	_auxtype  = PRODOS_AUX_T_BAS_PGM_LOAD_ADDR;
	return openfile(name, "r");
}

FILE *openasmfile(const char *name) 
{
	_filetype = PRODOS_T_TXT;
	_auxtype  = PRODOS_AUX_T_TXT_SEQ;
	return openfile(name, "w");
}

FILE *openbinfile(const char *name) 
{
	_filetype = PRODOS_T_BIN;
	_auxtype  = 0x0803; /* Binary hex load address */
	return openfile(name, "w");
}

FILE *openfile(const char *name, const char *mode)
{
	FILE *f;
	f = fopen(name, mode);
	if (f == NULL) {
		perror(name);
		exit(EXIT_FAILURE);
	}
}

/**
 * Any whitespace is removed from the right side of s.
 * @param s is modified
 */
void rtrim(char s[])
{
	size_t i;
	i = strlen(s);
	while (i > 0 && isspace(s[--i])) {
		s[i] = '\0';
	}
}

char *buildasmname(char *asmname, char *basname, size_t size)
{
	strncpy(asmname, basicfilename, size);
	if (strlen(asmname) > size - 2)
		asmname[size - 1] = '\0';
	strncat(asmname, ".s", size);
	return asmname;
}

void compile(FILE *basicfile, FILE *asmfile)
{
	int c;
	size_t i = 0;
	/* First 2 bytes are next line address.
	 * next 2 bytes are line number.
	 * next byte is beginning of token and chars */
	while ((c = fgetc(basicfile)) != EOF) {
		++i;
		printf("%d: %c %d\r", i, (char) c, c);
	}
}

