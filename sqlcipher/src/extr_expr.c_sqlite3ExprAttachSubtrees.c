#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_11__ {int flags; struct TYPE_11__* pLeft; struct TYPE_11__* pRight; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int EP_Propagate ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprSetHeight (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_1__*,TYPE_2__*) ; 

void sqlite3ExprAttachSubtrees(
  sqlite3 *db,
  Expr *pRoot,
  Expr *pLeft,
  Expr *pRight
){
  if( pRoot==0 ){
    assert( db->mallocFailed );
    sqlite3ExprDelete(db, pLeft);
    sqlite3ExprDelete(db, pRight);
  }else{
    if( pRight ){
      pRoot->pRight = pRight;
      pRoot->flags |= EP_Propagate & pRight->flags;
    }
    if( pLeft ){
      pRoot->pLeft = pLeft;
      pRoot->flags |= EP_Propagate & pLeft->flags;
    }
    exprSetHeight(pRoot);
  }
}