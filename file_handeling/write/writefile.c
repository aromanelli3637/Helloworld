#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	FILE *fp;
	char filepath[1024]="/home/fabricom/Helloworld/file_handeling/write/testfile.txt";
	char data[50] ="Hello World!\n";

	/* open & read file */
	fp = fopen(filepath, "a");
	if(fp == NULL)
	{
		 printf("Error: %s\n", strerror(errno));
	}
	fputs(data, fp);

	return 0;
}
