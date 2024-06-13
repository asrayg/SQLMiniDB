#include "query_executor.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

QueryExecutor::QueryExecutor(StorageManager& storageManager)
    : storageManager(storageManager) {}

void QueryExecutor::execute(const AST& ast) {
    switch (ast.type) {
        case SELECT:
            executeSelect(ast);
            break;
        case INSERT:
            executeInsert(ast);
            break;
        case UPDATE:
            executeUpdate(ast);
            break;
        case DELETE:
            executeDelete(ast);
            break;
        case CREATE_TABLE:
            executeCreateTable(ast);
            break;
        case DROP_TABLE:
            executeDropTable(ast);
            break;
        case ALTER_TABLE:
            executeAlterTable(ast);
            break;
        case TRUNCATE_TABLE:
            executeTruncateTable(ast);
            break;
        default:
            throw std::runtime_error("Unsupported SQL command");
    }
}

void QueryExecutor::executeSelect(const AST& ast) {
    Table table = storageManager.loadTable(ast.table);
    for (const auto& row : table.rows) {
        for (const auto& column : ast.columns) {
            int index = table.getColumnIndex(column);
            std::cout << row.values[index] << " ";
        }
        std::cout << "\n";
    }
}

void QueryExecutor::executeInsert(const AST& ast) {
    Table table = storageManager.loadTable(ast.table);
    Row row;
    row.values = ast.values;
    table.rows.push_back(row);
    storageManager.saveTable(table);
}

void QueryExecutor::executeUpdate(const AST& ast) {
    Table table = storageManager.loadTable(ast.table);
    for (auto& row : table.rows) {
        for (const auto& assignment : ast.columns) {
            std::istringstream ss(assignment);
            std::string column, value;
            std::getline(ss, column, '=');
            std::getline(ss, value);
            int index = table.getColumnIndex(column);
            row.values[index] = value;
        }
    }
    storageManager.saveTable(table);
}

void QueryExecutor::executeDelete(const AST& ast) {
    Table table = storageManager.loadTable(ast.table);
    auto it = table.rows.begin();
    while (it != table.rows.end()) {
        // Implement WHERE clause condition checking here.
        // If condition matches, erase the row.
        it = table.rows.erase(it);
    }
    storageManager.saveTable(table);
}

void QueryExecutor::executeCreateTable(const AST& ast) {
    Table table(ast.table, ast.table_definition);
    storageManager.saveTable(table);
    std::ofstream schemaFile(ast.table + ".schema");
    for (const auto& col : ast.table_definition) {
        schemaFile << col << " ";
    }
    schemaFile.close();
}

void QueryExecutor::executeDropTable(const AST& ast) {
    if (std::remove((ast.table + ".tbl").c_str()) != 0 || std::remove((ast.table + ".schema").c_str()) != 0) {
        throw std::runtime_error("Error deleting table");
    }
}

void QueryExecutor::executeAlterTable(const AST& ast) {
    Table table = storageManager.loadTable(ast.table);
    for (const auto& alteration : ast.columns) {
        std::istringstream ss(alteration);
        std::string action, column;
        ss >> action >> column;
        if (action == "ADD") {
            table.schema.push_back(column);
            table.schema_map[column] = table.schema.size() - 1;
            for (auto& row : table.rows) {
                row.values.push_back(""); 
            }
        } else if (action == "DROP") {
            int index = table.getColumnIndex(column);
            table.schema.erase(table.schema.begin() + index);
            for (auto& row : table.rows) {
                row.values.erase(row.values.begin() + index);
            }
            table.schema_map.clear();
            for (size_t i = 0; i < table.schema.size(); ++i) {
                table.schema_map[table.schema[i]] = i;
            }
        }
    }
    storageManager.saveTable(table);
    std::ofstream schemaFile(ast.table + ".schema");
    for (const auto& col : table.schema) {
        schemaFile << col << " ";
    }
    schemaFile.close();
}

void QueryExecutor::executeTruncateTable(const AST& ast) {
    Table table = storageManager.loadTable(ast.table);
    table.rows.clear();
    storageManager.saveTable(table);
}
