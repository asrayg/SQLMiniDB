#include "storage_manager.h"
#include <fstream>

void StorageManager::saveTable(const Table& table) {
    std::ofstream file(table.name + ".tbl");
    for (const auto& col : table.schema) {
        file << col << " ";
    }
    file << "\n";
    for (const auto& row : table.rows) {
        for (const auto& value : row.values) {
            file << value << " ";
        }
        file << "\n";
    }
}

Table StorageManager::loadTable(const std::string& tableName) {
    Table table(tableName, {});
    std::ifstream file(tableName + ".tbl");
    std::string col;
    while (file >> col) {
        table.schema.push_back(col);
        if (file.peek() == '\n') break;
    }
    for (size_t i = 0; i < table.schema.size(); ++i) {
        table.schema_map[table.schema[i]] = i;
    }
    std::string value;
    while (file >> value) {
        Row row;
        row.values.push_back(value);
        for (size_t i = 1; i < table.schema.size(); ++i) {
            file >> value;
            row.values.push_back(value);
        }
        table.rows.push_back(row);
    }
    return table;
}
