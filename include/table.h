#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <unordered_map>

struct Row {
    std::vector<std::string> values;
};

struct Table {
    std::string name;
    std::vector<std::string> schema;
    std::unordered_map<std::string, int> schema_map;
    std::vector<Row> rows;

    Table() = default;
    Table(const std::string& name, const std::vector<std::string>& schema);
    int getColumnIndex(const std::string& column);
};

#endif 