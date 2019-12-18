#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ eDetail; } ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_14__ {int /*<<< orphan*/  pExpr; TYPE_3__* pSorter; TYPE_1__ base; } ;
struct TYPE_13__ {int* a; int* b; } ;
struct TYPE_12__ {int* aIdx; int* aPoslist; } ;
struct TYPE_11__ {TYPE_6__* pConfig; } ;
typedef  TYPE_2__ Fts5Table ;
typedef  TYPE_3__ Fts5Sorter ;
typedef  TYPE_4__ Fts5PhraseIter ;
typedef  TYPE_5__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_6__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_COLUMNS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5ApiPhraseNextColumn (int /*<<< orphan*/ *,TYPE_4__*,int*) ; 
 int fts5CsrPoslist (TYPE_5__*,int,int**,int*) ; 
 scalar_t__ fts5GetVarint32 (int*,int) ; 
 int sqlite3Fts5ExprPhraseCollist (int /*<<< orphan*/ ,int,int**,int*) ; 

__attribute__((used)) static int fts5ApiPhraseFirstColumn(
  Fts5Context *pCtx, 
  int iPhrase, 
  Fts5PhraseIter *pIter, 
  int *piCol
){
  int rc = SQLITE_OK;
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  Fts5Config *pConfig = ((Fts5Table*)(pCsr->base.pVtab))->pConfig;

  if( pConfig->eDetail==FTS5_DETAIL_COLUMNS ){
    Fts5Sorter *pSorter = pCsr->pSorter;
    int n;
    if( pSorter ){
      int i1 = (iPhrase==0 ? 0 : pSorter->aIdx[iPhrase-1]);
      n = pSorter->aIdx[iPhrase] - i1;
      pIter->a = &pSorter->aPoslist[i1];
    }else{
      rc = sqlite3Fts5ExprPhraseCollist(pCsr->pExpr, iPhrase, &pIter->a, &n);
    }
    if( rc==SQLITE_OK ){
      pIter->b = &pIter->a[n];
      *piCol = 0;
      fts5ApiPhraseNextColumn(pCtx, pIter, piCol);
    }
  }else{
    int n;
    rc = fts5CsrPoslist(pCsr, iPhrase, &pIter->a, &n);
    if( rc==SQLITE_OK ){
      pIter->b = &pIter->a[n];
      if( n<=0 ){
        *piCol = -1;
      }else if( pIter->a[0]==0x01 ){
        pIter->a += 1 + fts5GetVarint32(&pIter->a[1], *piCol);
      }else{
        *piCol = 0;
      }
    }
  }

  return rc;
}