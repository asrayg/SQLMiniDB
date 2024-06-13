#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stack>
#include "table.h"

class TransactionManager {
public:
    void beginTransaction();
    void commit();
    void rollback();
    void addOperation(const Table& table);

private:
    std::stack<Table> transactionStack;
};

#endif 