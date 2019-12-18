#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_10__ {int n; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ Token ;
struct TYPE_9__ {int iValue; char* zToken; } ;
struct TYPE_11__ {int iAgg; int flags; int nHeight; TYPE_1__ u; scalar_t__ op; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int EP_IntValue ; 
 int EP_Leaf ; 
 int TK_INTEGER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3DequoteExpr (TYPE_3__*) ; 
 scalar_t__ sqlite3GetInt32 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ sqlite3Isquote (char) ; 

Expr *sqlite3ExprAlloc(
  sqlite3 *db,            /* Handle for sqlite3DbMallocRawNN() */
  int op,                 /* Expression opcode */
  const Token *pToken,    /* Token argument.  Might be NULL */
  int dequote             /* True to dequote */
){
  Expr *pNew;
  int nExtra = 0;
  int iValue = 0;

  assert( db!=0 );
  if( pToken ){
    if( op!=TK_INTEGER || pToken->z==0
          || sqlite3GetInt32(pToken->z, &iValue)==0 ){
      nExtra = pToken->n+1;
      assert( iValue>=0 );
    }
  }
  pNew = sqlite3DbMallocRawNN(db, sizeof(Expr)+nExtra);
  if( pNew ){
    memset(pNew, 0, sizeof(Expr));
    pNew->op = (u8)op;
    pNew->iAgg = -1;
    if( pToken ){
      if( nExtra==0 ){
        pNew->flags |= EP_IntValue|EP_Leaf;
        pNew->u.iValue = iValue;
      }else{
        pNew->u.zToken = (char*)&pNew[1];
        assert( pToken->z!=0 || pToken->n==0 );
        if( pToken->n ) memcpy(pNew->u.zToken, pToken->z, pToken->n);
        pNew->u.zToken[pToken->n] = 0;
        if( dequote && sqlite3Isquote(pNew->u.zToken[0]) ){
          sqlite3DequoteExpr(pNew);
        }
      }
    }
#if SQLITE_MAX_EXPR_DEPTH>0
    pNew->nHeight = 1;
#endif  
  }
  return pNew;
}