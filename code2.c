/*
 * code2.c 	-- Production of code for a stack machine
 *
 * Copyright © 2015 Erick Gallesio - I3S-CNRS/Polytech Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 21-Oct-2015 15:31 (eg)
 * Last file update:  4-Nov-2015 17:06 (eg)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "calc.h"
#include "syntax.h"

// ----------------------------------------------------------------------
//		Utilities
// ---------------------------------------------------------------------
#define LABEL(n)	 printf("L%03d:\n", n);	        // output a label

#define PROD0(op)	 printf("\t%s\n", op)
#define PROD1F(op,v)	 printf("\t%s\t%g\n", op, v)    // v is a float
#define PROD1S(op,v)	 printf("\t%s\t%s\n", op, v)    // v is a string
#define PROD1L(op,v)	 printf("\t%s\tL%03d\n", op, v) // v is a label


// ----------------------------------------------------------------------
//		Code production
//			This version produces code for a stack machine
// ---------------------------------------------------------------------
void produce_code(ast_node *n) {
  printf("Produire du code pour n = %p!!!!!\n", n);
}
