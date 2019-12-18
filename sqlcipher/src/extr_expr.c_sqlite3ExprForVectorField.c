#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* pList; } ;
struct TYPE_20__ {scalar_t__ op; int flags; int iColumn; scalar_t__ iTable; TYPE_3__ x; struct TYPE_20__* pLeft; } ;
struct TYPE_19__ {int /*<<< orphan*/  db; } ;
struct TYPE_17__ {TYPE_1__* a; } ;
struct TYPE_16__ {TYPE_5__* pExpr; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int EP_xIsSelect ; 
 scalar_t__ TK_SELECT ; 
 int /*<<< orphan*/  TK_SELECT_COLUMN ; 
 scalar_t__ TK_VECTOR ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* sqlite3ExprDup (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* sqlite3PExpr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3RenameTokenRemap (TYPE_4__*,TYPE_5__*,TYPE_5__*) ; 

Expr *sqlite3ExprForVectorField(
  Parse *pParse,       /* Parsing context */
  Expr *pVector,       /* The vector.  List of expressions or a sub-SELECT */
  int iField           /* Which column of the vector to return */
){
  Expr *pRet;
  if( pVector->op==TK_SELECT ){
    assert( pVector->flags & EP_xIsSelect );
    /* The TK_SELECT_COLUMN Expr node:
    **
    ** pLeft:           pVector containing TK_SELECT.  Not deleted.
    ** pRight:          not used.  But recursively deleted.
    ** iColumn:         Index of a column in pVector
    ** iTable:          0 or the number of columns on the LHS of an assignment
    ** pLeft->iTable:   First in an array of register holding result, or 0
    **                  if the result is not yet computed.
    **
    ** sqlite3ExprDelete() specifically skips the recursive delete of
    ** pLeft on TK_SELECT_COLUMN nodes.  But pRight is followed, so pVector
    ** can be attached to pRight to cause this node to take ownership of
    ** pVector.  Typically there will be multiple TK_SELECT_COLUMN nodes
    ** with the same pLeft pointer to the pVector, but only one of them
    ** will own the pVector.
    */
    pRet = sqlite3PExpr(pParse, TK_SELECT_COLUMN, 0, 0);
    if( pRet ){
      pRet->iColumn = iField;
      pRet->pLeft = pVector;
    }
    assert( pRet==0 || pRet->iTable==0 );
  }else{
    if( pVector->op==TK_VECTOR ) pVector = pVector->x.pList->a[iField].pExpr;
    pRet = sqlite3ExprDup(pParse->db, pVector, 0);
    sqlite3RenameTokenRemap(pParse, pRet, pVector);
  }
  return pRet;
}