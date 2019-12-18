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
struct TYPE_8__ {int isEof; int isRequireSeek; int isMatchinfoNeeded; scalar_t__ iPrevId; scalar_t__ bDesc; scalar_t__ iMaxDocid; scalar_t__ iMinDocid; int /*<<< orphan*/  pStmt; TYPE_1__* pExpr; } ;
struct TYPE_7__ {int bEof; scalar_t__ iDocid; } ;
typedef  TYPE_1__ Fts3Expr ;
typedef  TYPE_2__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3EvalNextRow (TYPE_2__*,TYPE_1__*,int*) ; 
 scalar_t__ sqlite3Fts3EvalTestDeferred (TYPE_2__*,int*) ; 
 scalar_t__ sqlite3_data_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts3EvalNext(Fts3Cursor *pCsr){
  int rc = SQLITE_OK;             /* Return Code */
  Fts3Expr *pExpr = pCsr->pExpr;
  assert( pCsr->isEof==0 );
  if( pExpr==0 ){
    pCsr->isEof = 1;
  }else{
    do {
      if( pCsr->isRequireSeek==0 ){
        sqlite3_reset(pCsr->pStmt);
      }
      assert( sqlite3_data_count(pCsr->pStmt)==0 );
      fts3EvalNextRow(pCsr, pExpr, &rc);
      pCsr->isEof = pExpr->bEof;
      pCsr->isRequireSeek = 1;
      pCsr->isMatchinfoNeeded = 1;
      pCsr->iPrevId = pExpr->iDocid;
    }while( pCsr->isEof==0 && sqlite3Fts3EvalTestDeferred(pCsr, &rc) );
  }

  /* Check if the cursor is past the end of the docid range specified
  ** by Fts3Cursor.iMinDocid/iMaxDocid. If so, set the EOF flag.  */
  if( rc==SQLITE_OK && (
        (pCsr->bDesc==0 && pCsr->iPrevId>pCsr->iMaxDocid)
     || (pCsr->bDesc!=0 && pCsr->iPrevId<pCsr->iMinDocid)
  )){
    pCsr->isEof = 1;
  }

  return rc;
}