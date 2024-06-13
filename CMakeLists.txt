cmake_minimum_required(VERSION 3.10)
project(my_database_engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(my_database_engine
    src/main.cpp
    src/query_executor.cpp
    src/sql_parser.cpp
    src/storage_manager.cpp
    src/table.cpp
    src/query_optimizer.cpp
    src/transaction_manager.cpp
)
