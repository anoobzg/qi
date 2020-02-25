#include <iostream>
#define ENIUQ(TEMPLATE) std::cout << TEMPLATE << "(" << #TEMPLATE << ");}";

void main()
{ENIUQ("#include <iostream.h>\n#define ENIUQ(TEMPLATE) std::cout << TEMPLATE<< \"(\" << #TEMPLATE << \");}\";\n\nvoid main()\n{ENIUQ");}