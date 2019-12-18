#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_8__ {TYPE_1__* pRoot; } ;
struct TYPE_7__ {int bEof; scalar_t__ bNomatch; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_1__ Fts5ExprNode ;
typedef  TYPE_2__ Fts5Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ExprNodeNext (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fts5RowidCmp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3Fts5ExprNext(Fts5Expr *p, i64 iLast){
  int rc;
  Fts5ExprNode *pRoot = p->pRoot;
  assert( pRoot->bEof==0 && pRoot->bNomatch==0 );
  do {
    rc = fts5ExprNodeNext(p, pRoot, 0, 0);
    assert( pRoot->bNomatch==0 || (rc==SQLITE_OK && pRoot->bEof==0) );
  }while( pRoot->bNomatch );
  if( fts5RowidCmp(p, pRoot->iRowid, iLast)>0 ){
    pRoot->bEof = 1;
  }
  return rc;
}