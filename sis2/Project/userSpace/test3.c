#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    char interval[20];
    printf("Hello please give time interval\n");
    fgets(interval,20,stdin);

	FILE *f = fopen("interval.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);	
	}



	fprintf(f, "%s", interval);

	fclose(f);

    char fileName[20];
    printf("Please give name of file to backapp\n");
    fgets(fileName,20,stdin);

	FILE *fa = fopen("fileName.txt", "w");
	if (fa == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);	
	}



	fprintf(fa, "%s", fileName);

	fclose(fa);
 
    return 0;
}
