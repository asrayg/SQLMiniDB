#include "sql_parser.h"
#include <sstream>
#include <stdexcept>

AST SQLParser::parse(const std::string& query) {
    std::istringstream stream(query);
    std::string command;
    stream >> command;
    if (command == "SELECT") {
        AST ast;
        ast.type = SELECT;
        std::string column;
        while (stream >> column) {
            if (column == "FROM") break;
            ast.columns.push_back(column);
        }
        stream >> ast.table;
        // Parse JOIN clauses if present
        std::string token;
        while (stream >> token) {
            if (token == "JOIN") {
                std::string join_table;
                stream >> join_table;
                ast.join_tables.push_back(join_table);
                std::string on;
                stream >> on; // should be "ON"
                std::string join_condition;
                std::getline(stream, join_condition);
                ast.join_conditions.push_back(join_condition);
            } else if (token == "WHERE") {
                std::getline(stream, ast.condition);
                break;
            }
        }
        return ast;
    } else if (command == "INSERT") {
        AST ast;
        ast.type = INSERT;
        std::string into;
        stream >> into >> ast.table;
        std::string values;
        stream >> values;
        if (values != "VALUES") {
            throw std::runtime_error("Syntax error in INSERT statement");
        }
        std::string value;
        while (stream >> value) {
            ast.values.push_back(value);
        }
        return ast;
    } else if (command == "UPDATE") {
        AST ast;
        ast.type = UPDATE;
        stream >> ast.table;
        std::string set;
        stream >> set;
        if (set != "SET") {
            throw std::runtime_error("Syntax error in UPDATE statement");
        }
        std::string assignment;
        while (stream >> assignment) {
            if (assignment == "WHERE") break;
            ast.columns.push_back(assignment);
        }
        std::getline(stream, ast.condition);
        return ast;
    } else if (command == "DELETE") {
        AST ast;
        ast.type = DELETE;
        std::string from;
        stream >> from >> ast.table;
        std::string where;
        stream >> where;
        if (where != "WHERE") {
            throw std::runtime_error("Syntax error in DELETE statement");
        }
        std::getline(stream, ast.condition);
        return ast;
    } else if (command == "CREATE") {
        std::string next_token;
        stream >> next_token;
        if (next_token == "TABLE") {
            AST ast;
            ast.type = CREATE_TABLE;
            stream >> ast.table;
            std::string definition;
            while (stream >> definition) {
                ast.table_definition.push_back(definition);
            }
            return ast;
        }
    } else if (command == "DROP") {
        std::string next_token;
        stream >> next_token;
        if (next_token == "TABLE") {
            AST ast;
            ast.type = DROP_TABLE;
            stream >> ast.table;
            return ast;
        }
    } else if (command == "ALTER") {
        std::string next_token;
        stream >> next_token;
        if (next_token == "TABLE") {
            AST ast;
            ast.type = ALTER_TABLE;
            stream >> ast.table;
            std::string alteration;
            while (stream >> alteration) {
                ast.columns.push_back(alteration);
            }
            return ast;
        }
    } else if (command == "TRUNCATE") {
        std::string next_token;
        stream >> next_token;
        if (next_token == "TABLE") {
            AST ast;
            ast.type = TRUNCATE_TABLE;
            stream >> ast.table;
            return ast;
        }
    }
    throw std::runtime_error("Unsupported SQL command");
}