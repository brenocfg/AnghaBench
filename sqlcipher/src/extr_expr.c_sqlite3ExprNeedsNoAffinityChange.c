#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ op; int op2; int /*<<< orphan*/  iColumn; int /*<<< orphan*/  iTable; struct TYPE_3__* pLeft; } ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 char SQLITE_AFF_BLOB ; 
 char SQLITE_AFF_INTEGER ; 
 char SQLITE_AFF_NUMERIC ; 
 char SQLITE_AFF_REAL ; 
 char SQLITE_AFF_TEXT ; 
#define  TK_BLOB 132 
#define  TK_COLUMN 131 
#define  TK_FLOAT 130 
#define  TK_INTEGER 129 
 int TK_REGISTER ; 
#define  TK_STRING 128 
 scalar_t__ TK_UMINUS ; 
 scalar_t__ TK_UPLUS ; 
 int /*<<< orphan*/  assert (int) ; 

int sqlite3ExprNeedsNoAffinityChange(const Expr *p, char aff){
  u8 op;
  if( aff==SQLITE_AFF_BLOB ) return 1;
  while( p->op==TK_UPLUS || p->op==TK_UMINUS ){ p = p->pLeft; }
  op = p->op;
  if( op==TK_REGISTER ) op = p->op2;
  switch( op ){
    case TK_INTEGER: {
      return aff==SQLITE_AFF_INTEGER || aff==SQLITE_AFF_NUMERIC;
    }
    case TK_FLOAT: {
      return aff==SQLITE_AFF_REAL || aff==SQLITE_AFF_NUMERIC;
    }
    case TK_STRING: {
      return aff==SQLITE_AFF_TEXT;
    }
    case TK_BLOB: {
      return 1;
    }
    case TK_COLUMN: {
      assert( p->iTable>=0 );  /* p cannot be part of a CHECK constraint */
      return p->iColumn<0
          && (aff==SQLITE_AFF_INTEGER || aff==SQLITE_AFF_NUMERIC);
    }
    default: {
      return 0;
    }
  }
}