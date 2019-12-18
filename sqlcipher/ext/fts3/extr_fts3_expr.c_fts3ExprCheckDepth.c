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
struct TYPE_3__ {struct TYPE_3__* pRight; struct TYPE_3__* pLeft; } ;
typedef  TYPE_1__ Fts3Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_TOOBIG ; 

__attribute__((used)) static int fts3ExprCheckDepth(Fts3Expr *p, int nMaxDepth){
  int rc = SQLITE_OK;
  if( p ){
    if( nMaxDepth<0 ){ 
      rc = SQLITE_TOOBIG;
    }else{
      rc = fts3ExprCheckDepth(p->pLeft, nMaxDepth-1);
      if( rc==SQLITE_OK ){
        rc = fts3ExprCheckDepth(p->pRight, nMaxDepth-1);
      }
    }
  }
  return rc;
}