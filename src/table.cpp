#include "table.h"

Table::Table(const std::string& name, const std::vector<std::string>& schema)
    : name(name), schema(schema) {
    for (size_t i = 0; i < schema.size(); ++i) {
        schema_map[schema[i]] = i;
    }
}

int Table::getColumnIndex(const std::string& column) {
    return schema_map.at(column);
}
