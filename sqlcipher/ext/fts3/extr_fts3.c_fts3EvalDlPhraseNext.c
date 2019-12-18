#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_6__ {char* aAll; size_t nAll; char* pNextDocid; char* pList; int nList; int /*<<< orphan*/  iDocid; } ;
struct TYPE_5__ {scalar_t__ bDescIdx; } ;
typedef  TYPE_1__ Fts3Table ;
typedef  TYPE_2__ Fts3Doclist ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3PoslistCopy (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,scalar_t__*) ; 

__attribute__((used)) static void fts3EvalDlPhraseNext(
  Fts3Table *pTab,
  Fts3Doclist *pDL,
  u8 *pbEof
){
  char *pIter;                            /* Used to iterate through aAll */
  char *pEnd = &pDL->aAll[pDL->nAll];     /* 1 byte past end of aAll */
 
  if( pDL->pNextDocid ){
    pIter = pDL->pNextDocid;
  }else{
    pIter = pDL->aAll;
  }

  if( pIter>=pEnd ){
    /* We have already reached the end of this doclist. EOF. */
    *pbEof = 1;
  }else{
    sqlite3_int64 iDelta;
    pIter += sqlite3Fts3GetVarint(pIter, &iDelta);
    if( pTab->bDescIdx==0 || pDL->pNextDocid==0 ){
      pDL->iDocid += iDelta;
    }else{
      pDL->iDocid -= iDelta;
    }
    pDL->pList = pIter;
    fts3PoslistCopy(0, &pIter);
    pDL->nList = (int)(pIter - pDL->pList);

    /* pIter now points just past the 0x00 that terminates the position-
    ** list for document pDL->iDocid. However, if this position-list was
    ** edited in place by fts3EvalNearTrim(), then pIter may not actually
    ** point to the start of the next docid value. The following line deals
    ** with this case by advancing pIter past the zero-padding added by
    ** fts3EvalNearTrim().  */
    while( pIter<pEnd && *pIter==0 ) pIter++;

    pDL->pNextDocid = pIter;
    assert( pIter>=&pDL->aAll[pDL->nAll] || *pIter );
    *pbEof = 0;
  }
}