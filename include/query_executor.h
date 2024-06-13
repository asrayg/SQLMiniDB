#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include "ast.h"
#include "table.h"
#include "storage_manager.h"

class QueryExecutor {
public:
    QueryExecutor(StorageManager& storageManager);
    void execute(const AST& ast);
private:
    StorageManager& storageManager;

    void executeSelect(const AST& ast);
    void executeInsert(const AST& ast);
    void executeUpdate(const AST& ast);
    void executeDelete(const AST& ast);
    void executeCreateTable(const AST& ast);
    void executeDropTable(const AST& ast);
    void executeAlterTable(const AST& ast);
    void executeTruncateTable(const AST& ast);
};

#endif 
