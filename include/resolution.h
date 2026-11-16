#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "ast.h"
#include "maths.h"

int		resolve_polynomial(t_ast_chain *ast, int degree);

// degrees
int		degree_zero(t_ast_chain *ast);
int		degree_one(t_ast_chain *ast);
int		degree_two(t_ast_chain *ast);

#endif