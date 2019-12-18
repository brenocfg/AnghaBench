#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  iFirstRowid; int /*<<< orphan*/ * pExpr; } ;
struct TYPE_8__ {int /*<<< orphan*/  pIndex; } ;
struct TYPE_9__ {TYPE_1__ p; } ;
typedef  TYPE_2__ Fts5FullTable ;
typedef  int /*<<< orphan*/  Fts5Expr ;
typedef  TYPE_3__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagSet (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_EOF ; 
 int /*<<< orphan*/  fts5CsrNewrow (TYPE_3__*) ; 
 scalar_t__ sqlite3Fts5ExprEof (int /*<<< orphan*/ *) ; 
 int sqlite3Fts5ExprFirst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fts5CursorFirst(Fts5FullTable *pTab, Fts5Cursor *pCsr, int bDesc){
  int rc;
  Fts5Expr *pExpr = pCsr->pExpr;
  rc = sqlite3Fts5ExprFirst(pExpr, pTab->p.pIndex, pCsr->iFirstRowid, bDesc);
  if( sqlite3Fts5ExprEof(pExpr) ){
    CsrFlagSet(pCsr, FTS5CSR_EOF);
  }
  fts5CsrNewrow(pCsr);
  return rc;
}