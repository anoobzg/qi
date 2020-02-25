#include <stdio.h> 
char* s = "#include <stdio.h>%cchar* s = %c%s%c;%cvoid main() { printf(s, 10, 34, s, 34, 10, 10); }%c";
void main() { printf(s, 10, 34, s, 34, 10, 10); }