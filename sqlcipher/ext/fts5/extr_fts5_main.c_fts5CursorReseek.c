#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_13__ {int bDesc; int /*<<< orphan*/  pExpr; TYPE_1__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  pIndex; } ;
struct TYPE_12__ {TYPE_2__ p; } ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagClear (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CsrFlagSet (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CsrFlagTest (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_EOF ; 
 int /*<<< orphan*/  FTS5CSR_REQUIRE_RESEEK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CsrNewrow (TYPE_4__*) ; 
 scalar_t__ sqlite3Fts5ExprEof (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5ExprFirst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ sqlite3Fts5ExprRowid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5CursorReseek(Fts5Cursor *pCsr, int *pbSkip){
  int rc = SQLITE_OK;
  assert( *pbSkip==0 );
  if( CsrFlagTest(pCsr, FTS5CSR_REQUIRE_RESEEK) ){
    Fts5FullTable *pTab = (Fts5FullTable*)(pCsr->base.pVtab);
    int bDesc = pCsr->bDesc;
    i64 iRowid = sqlite3Fts5ExprRowid(pCsr->pExpr);

    rc = sqlite3Fts5ExprFirst(pCsr->pExpr, pTab->p.pIndex, iRowid, bDesc);
    if( rc==SQLITE_OK &&  iRowid!=sqlite3Fts5ExprRowid(pCsr->pExpr) ){
      *pbSkip = 1;
    }

    CsrFlagClear(pCsr, FTS5CSR_REQUIRE_RESEEK);
    fts5CsrNewrow(pCsr);
    if( sqlite3Fts5ExprEof(pCsr->pExpr) ){
      CsrFlagSet(pCsr, FTS5CSR_EOF);
      *pbSkip = 1;
    }
  }
  return rc;
}