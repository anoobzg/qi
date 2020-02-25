#include <stdio.h> 
char buff[200];
void main()
{
    FILE* fp;

    fp = fopen(__FILE__, "r");
    while (!feof(fp)) {
        printf("%s", fgets(buff, 199, fp));
    }
    fclose(fp);
}