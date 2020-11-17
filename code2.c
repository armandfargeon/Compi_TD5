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
static int i = 0;

// ----------------------------------------------------------------------
//		Code production
//			This version produces code for a stack machine
// ---------------------------------------------------------------------
void produce_code(ast_node *n) {
  //  printf("Produire du code pour n = %p!!!!!\n", n);
    switch (AST_KIND(n)) {
        case k_number:
            PROD1F("push",  NUMBER_VALUE(n));
            return;
        case k_ident:
            PROD1S("load", VAR_NAME(n));
            return;
        case k_operator: {
            ast_node **op = OPER_OPERANDS(n);
            int arity = OPER_ARITY(n);
            switch (OPER_OPERATOR(n)) {
                case UMINUS:
                    PROD1F("push",  (-1.0));
                    produce_code(op[0]);
                    PROD0("mul");
                    break;
                case EQ:
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("cmpeq");
                    break;
                case NE:
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("cmpne");
                    break;
                case LE:
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("cmple");
                    break;
                case GE:
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("cmpge");
                    break;
                case '>':
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("cmpgt");
                    break;
                case '<':
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("cmplt");
                    break;
                case '=':
                    produce_code(op[1]);
                    PROD1S("store",VAR_NAME(op[0]));
                    break;

                case '+':
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("add");
                    break;
                case '-':
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("sub");
                    break;

                case '*':
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("mul");
                    break;

                case '/':
                    produce_code(op[0]);
                    produce_code(op[1]);
                    PROD0("div");
                    break;

                case KIF:
                    produce_code(op[0]);
                    //jump to the end (or else)
                    int end = i++;
                    PROD1L("jumpz", end);
                    produce_code(op[1]);
                    if(arity == 3) {
                        int startElse = end;
                        end = i++;
                        PROD1L("jump", end);
                        LABEL(startElse);
                        produce_code(op[2]);
                    }
                    LABEL(end);
                    break;

                case KELSE:
                    produce_code(op[0]);
                    break;

                case KWHILE:
                    ;int start = i++;
                    int end_w = i++;
                    LABEL(start);
                    produce_code(op[0]);
                    //if condition is false, jump to the end
                    PROD1L("jumpz", end_w);
                    //expr inside the while
                    produce_code(op[1]);
                    //back to the while label
                    PROD1L("jump", start);
                    //continue after the end of the loop
                    LABEL(end_w);
                    break;

                case KPRINT:
                    produce_code(op[0]);
                    PROD0("print");
                    break;

                case KREAD:
                    PROD1S("read", VAR_NAME(op[0]));
                    break;

                case ';':
                    if (arity == 0) break;
                    else {
                        produce_code(op[0]);
                        produce_code(op[1]);
                    }
            }

        }

    }

}
