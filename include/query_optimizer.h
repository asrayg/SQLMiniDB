#ifndef QUERY_OPTIMIZER_H
#define QUERY_OPTIMIZER_H

#include "ast.h"

class QueryOptimizer {
public:
    AST optimize(const AST& ast);
};

#endif 