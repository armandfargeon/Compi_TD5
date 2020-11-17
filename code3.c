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

// ----------------------------------------------------------------------
//		Utilities
// ---------------------------------------------------------------------
#define BOX_LINK(p,f)	 printf("\t\tbox%d -> box%d;\n", p, f)
#define BOX_V(no,v)	 printf("\tbox%d [label=\"%s\", fillcolor=\"peru\"];\n", no, v)
#define BOX_N(no,n)	 printf("\tbox%d [label=\"%g\", fillcolor=\"tomato\"];\n", no, n)
#define BOX_K(no,k)	 printf("\tbox%d [label=\"%s\", fillcolor=\"turquoise4\"];\n", no, k)
static int i = 1;

void prod(ast_node *n) {
    switch (AST_KIND(n)) {
        case k_number:
            BOX_N(i++,NUMBER_VALUE(n));
            return;
        case k_ident:
            BOX_V(i++,VAR_NAME(n));
            return;
        case k_operator: {
            ast_node **op = OPER_OPERANDS(n);
            int arity = OPER_ARITY(n);
            int root = i;
            switch (OPER_OPERATOR(n)) {
                case UMINUS:
                    BOX_K(i++, "[_]");
                    int t = i;
                    prod(op[0]);
                    BOX_LINK(root, t);
                    return;
                case EQ:
                    BOX_K(i++, "[==]");
                    break;
                case NE:
                    BOX_K(i++, "[!=]");
                    break;
                case LE:
                    BOX_K(i++, "[<=]");
                    break;
                case GE:
                    BOX_K(i++, "[>=]");
                    break;
                case '>':
                    BOX_K(i++, "[>]");
                    break;
                case '<':
                    BOX_K(i++, "[<]");
                    break;
                case '=':
                    BOX_K(i++, "[=]");
                    break;

                case '+':
                    BOX_K(i++, "[+]");
                    break;
                case '-':
                    BOX_K(i++, "[-]");
                    break;

                case '*':
                    BOX_K(i++, "[*]");
                    break;

                case '/':
                    BOX_K(i++, "[/]");
                    break;

                case KIF:
                    BOX_K(i++, "if");
                    break;

                case KELSE:
                    BOX_K(i++, "else");
                    break;

                case KWHILE:
                    BOX_K(i++, "while");
                    break;

                case KPRINT:
                    BOX_K(i++, "print");
                    break;
                
                case KREAD:
                    BOX_K(i++, "read");
                    break;

                case ';':
                    if (arity == 0) return;
                    else {
                        BOX_K(i++, "[;]");
                    }
            }
            prod(op[0]);
            BOX_LINK(root, root+1);
            if(arity > 1) {
                int next = i;
                prod(op[1]);
                BOX_LINK(root, next);
            }
            if(arity==3){
                int last = i;
                prod(op[2]);
                BOX_LINK(root, last);
            }
        }
    }
}


void produce_code(ast_node *n) {
  printf("digraph E{\n");
  printf("\tnode [style=\"filled\"];\n");
  prod(n);
  printf("}\n");
}


