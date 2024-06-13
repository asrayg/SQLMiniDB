#include "transaction_manager.h"

void TransactionManager::beginTransaction() {
    transactionStack.push(Table("", {}));
}

void TransactionManager::commit() {
    while (!transactionStack.empty()) {
        transactionStack.pop();
    }
}

void TransactionManager::rollback() {
    if (!transactionStack.empty()) {
        transactionStack.pop();
    }
}

void TransactionManager::addOperation(const Table& table) {
    if (!transactionStack.empty()) {
        transactionStack.top() = table;
    }
}
