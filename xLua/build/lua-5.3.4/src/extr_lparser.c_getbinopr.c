#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BinOpr ;

/* Variables and functions */
 int /*<<< orphan*/  OPR_ADD ; 
 int /*<<< orphan*/  OPR_AND ; 
 int /*<<< orphan*/  OPR_BAND ; 
 int /*<<< orphan*/  OPR_BOR ; 
 int /*<<< orphan*/  OPR_BXOR ; 
 int /*<<< orphan*/  OPR_CONCAT ; 
 int /*<<< orphan*/  OPR_DIV ; 
 int /*<<< orphan*/  OPR_EQ ; 
 int /*<<< orphan*/  OPR_GE ; 
 int /*<<< orphan*/  OPR_GT ; 
 int /*<<< orphan*/  OPR_IDIV ; 
 int /*<<< orphan*/  OPR_LE ; 
 int /*<<< orphan*/  OPR_LT ; 
 int /*<<< orphan*/  OPR_MOD ; 
 int /*<<< orphan*/  OPR_MUL ; 
 int /*<<< orphan*/  OPR_NE ; 
 int /*<<< orphan*/  OPR_NOBINOPR ; 
 int /*<<< orphan*/  OPR_OR ; 
 int /*<<< orphan*/  OPR_POW ; 
 int /*<<< orphan*/  OPR_SHL ; 
 int /*<<< orphan*/  OPR_SHR ; 
 int /*<<< orphan*/  OPR_SUB ; 
#define  TK_AND 137 
#define  TK_CONCAT 136 
#define  TK_EQ 135 
#define  TK_GE 134 
#define  TK_IDIV 133 
#define  TK_LE 132 
#define  TK_NE 131 
#define  TK_OR 130 
#define  TK_SHL 129 
#define  TK_SHR 128 

__attribute__((used)) static BinOpr getbinopr (int op) {
  switch (op) {
    case '+': return OPR_ADD;
    case '-': return OPR_SUB;
    case '*': return OPR_MUL;
    case '%': return OPR_MOD;
    case '^': return OPR_POW;
    case '/': return OPR_DIV;
    case TK_IDIV: return OPR_IDIV;
    case '&': return OPR_BAND;
    case '|': return OPR_BOR;
    case '~': return OPR_BXOR;
    case TK_SHL: return OPR_SHL;
    case TK_SHR: return OPR_SHR;
    case TK_CONCAT: return OPR_CONCAT;
    case TK_NE: return OPR_NE;
    case TK_EQ: return OPR_EQ;
    case '<': return OPR_LT;
    case TK_LE: return OPR_LE;
    case '>': return OPR_GT;
    case TK_GE: return OPR_GE;
    case TK_AND: return OPR_AND;
    case TK_OR: return OPR_OR;
    default: return OPR_NOBINOPR;
  }
}