#ifndef SQL_PARSER_H
#define SQL_PARSER_H

#include <string>
#include "ast.h"

class SQLParser {
public:
    AST parse(const std::string& query);
};

#endif 