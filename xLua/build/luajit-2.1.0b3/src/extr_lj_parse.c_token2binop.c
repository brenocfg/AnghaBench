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
typedef  int LexToken ;
typedef  int /*<<< orphan*/  BinOpr ;

/* Variables and functions */
 int /*<<< orphan*/  OPR_ADD ; 
 int /*<<< orphan*/  OPR_AND ; 
 int /*<<< orphan*/  OPR_CONCAT ; 
 int /*<<< orphan*/  OPR_DIV ; 
 int /*<<< orphan*/  OPR_EQ ; 
 int /*<<< orphan*/  OPR_GE ; 
 int /*<<< orphan*/  OPR_GT ; 
 int /*<<< orphan*/  OPR_LE ; 
 int /*<<< orphan*/  OPR_LT ; 
 int /*<<< orphan*/  OPR_MOD ; 
 int /*<<< orphan*/  OPR_MUL ; 
 int /*<<< orphan*/  OPR_NE ; 
 int /*<<< orphan*/  OPR_NOBINOPR ; 
 int /*<<< orphan*/  OPR_OR ; 
 int /*<<< orphan*/  OPR_POW ; 
 int /*<<< orphan*/  OPR_SUB ; 
#define  TK_and 134 
#define  TK_concat 133 
#define  TK_eq 132 
#define  TK_ge 131 
#define  TK_le 130 
#define  TK_ne 129 
#define  TK_or 128 

__attribute__((used)) static BinOpr token2binop(LexToken tok)
{
  switch (tok) {
  case '+':	return OPR_ADD;
  case '-':	return OPR_SUB;
  case '*':	return OPR_MUL;
  case '/':	return OPR_DIV;
  case '%':	return OPR_MOD;
  case '^':	return OPR_POW;
  case TK_concat: return OPR_CONCAT;
  case TK_ne:	return OPR_NE;
  case TK_eq:	return OPR_EQ;
  case '<':	return OPR_LT;
  case TK_le:	return OPR_LE;
  case '>':	return OPR_GT;
  case TK_ge:	return OPR_GE;
  case TK_and:	return OPR_AND;
  case TK_or:	return OPR_OR;
  default:	return OPR_NOBINOPR;
  }
}