#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	FILE *fp;
	char filepath[1024];
	char output[2048];

	/* get filepath */
	printf("Enter filepath :\n");
	fgets(filepath, 1024, stdin);
	printf("Filepath: %s",filepath);
	filepath[strlen(filepath) - 1] = '\0';

	/* open & read file */
	fp = fopen(filepath, "r");
	if(fp == NULL)
	{
		 printf("Error: %s\n", strerror(errno));
	}

	fread(output, 1, 1024, fp);

	/* print */
	for(int i=0; i<1024; i++)
	{
		printf("%c", output[i]);
	}
	return 0;
}
