#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iValue; int /*<<< orphan*/  zToken; } ;
struct TYPE_5__ {int op; int flags; struct TYPE_5__* pLeft; TYPE_1__ u; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int EP_IntValue ; 
 int TK_INTEGER ; 
#define  TK_UMINUS 129 
#define  TK_UPLUS 128 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3GetInt32 (int /*<<< orphan*/ ,int*) ; 

int sqlite3ExprIsInteger(Expr *p, int *pValue){
  int rc = 0;
  if( p==0 ) return 0;  /* Can only happen following on OOM */

  /* If an expression is an integer literal that fits in a signed 32-bit
  ** integer, then the EP_IntValue flag will have already been set */
  assert( p->op!=TK_INTEGER || (p->flags & EP_IntValue)!=0
           || sqlite3GetInt32(p->u.zToken, &rc)==0 );

  if( p->flags & EP_IntValue ){
    *pValue = p->u.iValue;
    return 1;
  }
  switch( p->op ){
    case TK_UPLUS: {
      rc = sqlite3ExprIsInteger(p->pLeft, pValue);
      break;
    }
    case TK_UMINUS: {
      int v;
      if( sqlite3ExprIsInteger(p->pLeft, &v) ){
        assert( v!=(-2147483647-1) );
        *pValue = -v;
        rc = 1;
      }
      break;
    }
    default: break;
  }
  return rc;
}