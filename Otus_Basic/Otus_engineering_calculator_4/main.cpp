// OTUS C++ Basic course homework skeleton.
// Lexer using example

#include <iostream>

#include "astnode.h"
#include "lexer.h"
#include "parser.h"

int main()
{

    Lexer lexer(std::cin);
    Parser parser(lexer);

    ASTNode *ast = parser.parse();
    if (ast)
    {
        ast->print(std::cout);
    }

    return 0;
}
