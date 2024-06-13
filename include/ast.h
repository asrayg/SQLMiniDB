#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

enum ASTNodeType {
    SELECT,
    INSERT,
    UPDATE,
    DELETE,
    CREATE_TABLE,
    DROP_TABLE,
    ALTER_TABLE,
    TRUNCATE_TABLE
};

struct AST {
    ASTNodeType type;
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::string> values;
    std::string condition;
    std::vector<std::string> table_definition; 
};

#endif 
