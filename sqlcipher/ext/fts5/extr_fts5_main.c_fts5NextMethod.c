#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_7__ {int ePlan; int /*<<< orphan*/  pStmt; int /*<<< orphan*/  pExpr; int /*<<< orphan*/  iLastRowid; } ;
typedef  TYPE_1__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagSet (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CsrFlagTest (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_EOF ; 
 int FTS5_PLAN_MATCH ; 
#define  FTS5_PLAN_SORTED_MATCH 129 
 int FTS5_PLAN_SOURCE ; 
#define  FTS5_PLAN_SPECIAL 128 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CsrNewrow (TYPE_1__*) ; 
 int fts5CursorReseek (TYPE_1__*,int*) ; 
 int fts5SorterNext (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3Fts5ExprEof (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5ExprNext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5NextMethod(sqlite3_vtab_cursor *pCursor){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCursor;
  int rc;

  assert( (pCsr->ePlan<3)==
          (pCsr->ePlan==FTS5_PLAN_MATCH || pCsr->ePlan==FTS5_PLAN_SOURCE) 
  );
  assert( !CsrFlagTest(pCsr, FTS5CSR_EOF) );

  if( pCsr->ePlan<3 ){
    int bSkip = 0;
    if( (rc = fts5CursorReseek(pCsr, &bSkip)) || bSkip ) return rc;
    rc = sqlite3Fts5ExprNext(pCsr->pExpr, pCsr->iLastRowid);
    CsrFlagSet(pCsr, sqlite3Fts5ExprEof(pCsr->pExpr));
    fts5CsrNewrow(pCsr);
  }else{
    switch( pCsr->ePlan ){
      case FTS5_PLAN_SPECIAL: {
        CsrFlagSet(pCsr, FTS5CSR_EOF);
        rc = SQLITE_OK;
        break;
      }
  
      case FTS5_PLAN_SORTED_MATCH: {
        rc = fts5SorterNext(pCsr);
        break;
      }
  
      default:
        rc = sqlite3_step(pCsr->pStmt);
        if( rc!=SQLITE_ROW ){
          CsrFlagSet(pCsr, FTS5CSR_EOF);
          rc = sqlite3_reset(pCsr->pStmt);
        }else{
          rc = SQLITE_OK;
        }
        break;
    }
  }
  
  return rc;
}