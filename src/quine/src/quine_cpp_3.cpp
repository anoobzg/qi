#include <stdio.h>
const char* str = "#include <stdio.h>%cconst char* str = %c%s%c;%cint main(int argc, char* argv[])%c{%c   printf(str, 10, 34, str, 34, 10, 10, 10, 10, 10);%c   return 0;%c}";
int main(int argc, char* argv[])
{
	printf(str, 10, 34, str, 34, 10, 10, 10, 10, 10);
	return 0;
}
