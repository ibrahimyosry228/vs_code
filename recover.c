#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
	printf("Usage: ./recover IMAGE\n");
	return 1;
    }
    FILE *memory = fopen(argv[1], "r");
    if(memory == NULL)
    {
	printf("failed to read card\n");
	return 1;
    }
    char buffer[512];
    char filename[8];
    int count = 0;
    FILE *output = fopen("test.jpg", "w");
    if (output == NULL)
    {
	printf("failed to create file\n");
	return 1;
    }
    while (fread(&buffer, 1, 512, memory) == 512)
    {
	if(buffer[0] == (char) 0xff && buffer[1] == (char) 0xd8 && buffer[2] == (char) 0xff/* && (buffer[3] & (char) 0xf0) == (char) 0xe0*/)
	{
	    fclose(output);
	    sprintf(filename, "%03i.jpg", count);
	    count++;
            output = fopen(filename, "w");
	    if (output == NULL)                            {                                                  printf("failed to create file\n");             return 1;                                  }

	}
	fwrite(&buffer, 512, 1, output);
    }

    fclose(output);
    fclose(memory);

    return 0;
}
