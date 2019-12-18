#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {TYPE_2__* pTab; } ;
struct TYPE_10__ {scalar_t__ op; int op2; size_t iColumn; TYPE_3__ y; struct TYPE_10__* pLeft; } ;
struct TYPE_8__ {TYPE_1__* aCol; } ;
struct TYPE_7__ {int /*<<< orphan*/  notNull; } ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_CanBeNull ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_4__ const*,int /*<<< orphan*/ ) ; 
#define  TK_BLOB 132 
#define  TK_COLUMN 131 
#define  TK_FLOAT 130 
#define  TK_INTEGER 129 
 int TK_REGISTER ; 
#define  TK_STRING 128 
 scalar_t__ TK_UMINUS ; 
 scalar_t__ TK_UPLUS ; 

int sqlite3ExprCanBeNull(const Expr *p){
  u8 op;
  while( p->op==TK_UPLUS || p->op==TK_UMINUS ){
    p = p->pLeft;
  }
  op = p->op;
  if( op==TK_REGISTER ) op = p->op2;
  switch( op ){
    case TK_INTEGER:
    case TK_STRING:
    case TK_FLOAT:
    case TK_BLOB:
      return 0;
    case TK_COLUMN:
      return ExprHasProperty(p, EP_CanBeNull) ||
             p->y.pTab==0 ||  /* Reference to column of index on expression */
             (p->iColumn>=0 && p->y.pTab->aCol[p->iColumn].notNull==0);
    default:
      return 1;
  }
}