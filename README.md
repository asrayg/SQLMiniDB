# SQLMiniDB

SQLMiniDB is a lightweight SQL database engine implemented in C++. It supports basic SQL commands such as SELECT, INSERT, UPDATE, DELETE, CREATE TABLE, DROP TABLE, ALTER TABLE, and TRUNCATE TABLE. I made this project as an educational tool to understand the inner workings of a database engine.

## Features

- SQL Parsing
- Query Optimization
- Query Execution
- Transaction Management
- Basic Indexing (Placeholder)
- Join Reordering (Placeholder)

## Project Structure

```
SQLMiniDB/
├── CMakeLists.txt
├── include/
│   ├── ast.h
│   ├── query_executor.h
│   ├── sql_parser.h
│   ├── storage_manager.h
│   ├── table.h
│   ├── query_optimizer.h
│   └── transaction_manager.h
├── src/
│   ├── main.cpp
│   ├── query_executor.cpp
│   ├── sql_parser.cpp
│   ├── storage_manager.cpp
│   ├── table.cpp
│   ├── query_optimizer.cpp
│   └── transaction_manager.cpp
└── tests/
    └── test.cpp
```

## Prerequisites

- CMake 3.10 or higher
- A C++17 compatible compiler (e.g., GCC, Clang)

## Setup

### Building the Project

1. Clone the repository:

   ```bash
   git clone https://github.com/asrayg/SQLMiniDB.git
   cd SQLMiniDB
   ```

2. Create a build directory:

   ```bash
   mkdir build
   cd build
   ```

3. Run CMake to generate the build system:

   ```bash
   cmake ..
   ```

4. Build the project:

   ```bash
   make
   ```

### Running the Tests

1. Run the tests using CTest:

   ```bash
   ctest
   ```

## Usage

After building the project, you can run the executable and execute SQL commands interactively.

```bash
./SQLMiniDB
```

### Example SQL Commands

```sql
CREATE TABLE employees (id, name, position);
INSERT INTO employees VALUES (1, 'Alice', 'Manager');
INSERT INTO employees VALUES (2, 'Bob', 'Developer');
SELECT id, name FROM employees WHERE position = 'Developer';
UPDATE employees SET name = 'Charlie' WHERE id = 2;
DELETE FROM employees WHERE id = 1;
DROP TABLE employees;
```

## Code Overview

### SQL Parsing

The SQL parser converts SQL queries into an abstract syntax tree (AST) representation.

### Query Optimization

The query optimizer improves the efficiency of query execution by applying various optimization techniques such as removing unnecessary columns and reordering joins.

### Query Execution

The query executor processes the AST and performs the necessary operations on the database.

### Transaction Management

The transaction manager ensures ACID properties (Atomicity, Consistency, Isolation, Durability) for database transactions.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests for improvements and new features.

## License

This project is licensed under the MIT License.

## Acknowledgments

Inspired by various database systems and educational resources on SQL and database management systems.
