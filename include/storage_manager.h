#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <string>
#include "table.h"

class StorageManager {
public:
    void saveTable(const Table& table);
    Table loadTable(const std::string& tableName);
};

#endif
