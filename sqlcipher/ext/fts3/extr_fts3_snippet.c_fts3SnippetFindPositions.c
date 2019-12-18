#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pPhrase; } ;
struct TYPE_9__ {int /*<<< orphan*/  iCol; int /*<<< orphan*/  pCsr; TYPE_2__* aPhrase; } ;
struct TYPE_8__ {char* pList; char* pHead; char* pTail; int iHead; int iTail; int /*<<< orphan*/  nToken; } ;
struct TYPE_7__ {int /*<<< orphan*/  nToken; } ;
typedef  TYPE_2__ SnippetPhrase ;
typedef  TYPE_3__ SnippetIter ;
typedef  TYPE_4__ Fts3Expr ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3GetDeltaPosition (char**,int*) ; 
 int sqlite3Fts3EvalPhrasePoslist (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int fts3SnippetFindPositions(Fts3Expr *pExpr, int iPhrase, void *ctx){
  SnippetIter *p = (SnippetIter *)ctx;
  SnippetPhrase *pPhrase = &p->aPhrase[iPhrase];
  char *pCsr;
  int rc;

  pPhrase->nToken = pExpr->pPhrase->nToken;
  rc = sqlite3Fts3EvalPhrasePoslist(p->pCsr, pExpr, p->iCol, &pCsr);
  assert( rc==SQLITE_OK || pCsr==0 );
  if( pCsr ){
    int iFirst = 0;
    pPhrase->pList = pCsr;
    fts3GetDeltaPosition(&pCsr, &iFirst);
    if( iFirst<0 ){
      rc = FTS_CORRUPT_VTAB;
    }else{
      pPhrase->pHead = pCsr;
      pPhrase->pTail = pCsr;
      pPhrase->iHead = iFirst;
      pPhrase->iTail = iFirst;
    }
  }else{
    assert( rc!=SQLITE_OK || (
       pPhrase->pList==0 && pPhrase->pHead==0 && pPhrase->pTail==0 
    ));
  }

  return rc;
}