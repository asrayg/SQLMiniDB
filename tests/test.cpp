#include <iostream>
#include <cassert>
#include "../include/sql_parser.h"
#include "../include/query_executor.h"
#include "../include/storage_manager.h"
#include "../include/query_optimizer.h"
#include "../include/transaction_manager.h"

void testSQLParser() {
    SQLParser parser;
    
    AST selectAST = parser.parse("SELECT column1, column2 FROM table1 WHERE column1 = 'value1'");
    assert(selectAST.type == SELECT);
    assert(selectAST.columns == std::vector<std::string>{"column1", "column2"});
    assert(selectAST.table == "table1");
    assert(selectAST.condition == " column1 = 'value1'");
    
=    AST insertAST = parser.parse("INSERT INTO table1 VALUES ('value1', 'value2')");
    assert(insertAST.type == INSERT);
    assert(insertAST.table == "table1");
    assert(insertAST.values == std::vector<std::string>{"'value1'", "'value2'"});
    
    AST updateAST = parser.parse("UPDATE table1 SET column1='newvalue' WHERE column1='oldvalue'");
    assert(updateAST.type == UPDATE);
    assert(updateAST.table == "table1");
    assert(updateAST.columns == std::vector<std::string>{"column1='newvalue'"});
    assert(updateAST.condition == " column1='oldvalue'");
    
    AST deleteAST = parser.parse("DELETE FROM table1 WHERE column1='value1'");
    assert(deleteAST.type == DELETE);
    assert(deleteAST.table == "table1");
    assert(deleteAST.condition == " column1='value1'");
    
    AST createTableAST = parser.parse("CREATE TABLE table1 (column1, column2)");
    assert(createTableAST.type == CREATE_TABLE);
    assert(createTableAST.table == "table1");
    assert(createTableAST.table_definition == std::vector<std::string>{"column1,", "column2"});
    
    AST dropTableAST = parser.parse("DROP TABLE table1");
    assert(dropTableAST.type == DROP_TABLE);
    assert(dropTableAST.table == "table1");
    
    AST alterTableAST = parser.parse("ALTER TABLE table1 ADD column3");
    assert(alterTableAST.type == ALTER_TABLE);
    assert(alterTableAST.table == "table1");
    assert(alterTableAST.columns == std::vector<std::string>{"ADD column3"});
    
    AST truncateTableAST = parser.parse("TRUNCATE TABLE table1");
    assert(truncateTableAST.type == TRUNCATE_TABLE);
    assert(truncateTableAST.table == "table1");

    std::cout << "SQLParser tests passed." << std::endl;
}

void testQueryOptimizer() {
    QueryOptimizer optimizer;
    
    AST selectAST;
    selectAST.type = SELECT;
    selectAST.columns = {"column1", "column2", "column3"};
    selectAST.table = "table1";
    selectAST.condition = "column1 = 'value1'";
    
    AST optimizedAST = optimizer.optimize(selectAST);
    assert(optimizedAST.columns == std::vector<std::string>{"column1", "column2", "column3"});
    
    std::cout << "QueryOptimizer tests passed." << std::endl;
}

void testQueryExecutor() {
    StorageManager storageManager;
    QueryExecutor executor(storageManager);
    
    AST createTableAST;
    createTableAST.type = CREATE_TABLE;
    createTableAST.table = "table1";
    createTableAST.table_definition = {"column1", "column2"};
    
    executor.execute(createTableAST);
    Table table = storageManager.loadTable("table1");
    assert(table.name == "table1");
    assert(table.schema == std::vector<std::string>{"column1", "column2"});
    
    AST insertAST;
    insertAST.type = INSERT;
    insertAST.table = "table1";
    insertAST.values = {"value1", "value2"};
    
    executor.execute(insertAST);
    table = storageManager.loadTable("table1");
    assert(table.rows.size() == 1);
    assert(table.rows[0].values == std::vector<std::string>{"value1", "value2"});
    
    AST selectAST;
    selectAST.type = SELECT;
    selectAST.columns = {"column1", "column2"};
    selectAST.table = "table1";
    
    executor.execute(selectAST); // Verify output manually
    
    AST updateAST;
    updateAST.type = UPDATE;
    updateAST.table = "table1";
    updateAST.columns = {"column1='newvalue'"};
    updateAST.condition = "column1='value1'";
    
    executor.execute(updateAST);
    table = storageManager.loadTable("table1");
    assert(table.rows[0].values[0] == "newvalue");
    
    AST deleteAST;
    deleteAST.type = DELETE;
    deleteAST.table = "table1";
    deleteAST.condition = "column1='newvalue'";
    
    executor.execute(deleteAST);
    table = storageManager.loadTable("table1");
    assert(table.rows.empty());
    
    std::cout << "QueryExecutor tests passed." << std::endl;
}

int main() {
    testSQLParser();
    testQueryOptimizer();
    testQueryExecutor();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
