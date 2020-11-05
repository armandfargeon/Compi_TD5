/*
 * code2.c 	-- Production of code for a stack machine
 *
 * Copyright © 2015 Erick Gallesio - I3S-CNRS/Polytech Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-Oct-2015 22:48 (eg)
 * Last file update:  4-Nov-2015 17:09 (eg)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calc.h"
#include "syntax.h"


// ----------------------------------------------------------------------
//		Code production
//			This version produces a dot file
// ---------------------------------------------------------------------
void produce_code(ast_node *n) {
  printf("digraph E{\n");
  printf("\tnode [style=\"filled\"];\n");
  printf("\tGraph of %p\n", n); 
  printf("}\n");
}
