#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {scalar_t__ pVtab; } ;
struct TYPE_16__ {scalar_t__ bDesc; TYPE_1__ base; } ;
struct TYPE_15__ {int /*<<< orphan*/  pNextDocid; int /*<<< orphan*/  pList; int /*<<< orphan*/  nList; int /*<<< orphan*/  iDocid; scalar_t__ nAll; int /*<<< orphan*/  aAll; } ;
struct TYPE_14__ {scalar_t__ bIncr; TYPE_4__ doclist; } ;
struct TYPE_13__ {scalar_t__ bDescIdx; } ;
typedef  TYPE_2__ Fts3Table ;
typedef  TYPE_3__ Fts3Phrase ;
typedef  TYPE_4__ Fts3Doclist ;
typedef  TYPE_5__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3EvalDlPhraseNext (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int fts3EvalIncrPhraseNext (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3Fts3DoclistPrev (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3EvalPhraseNext(
  Fts3Cursor *pCsr,               /* FTS Cursor handle */
  Fts3Phrase *p,                  /* Phrase object to advance to next docid */
  u8 *pbEof                       /* OUT: Set to 1 if EOF */
){
  int rc = SQLITE_OK;
  Fts3Doclist *pDL = &p->doclist;
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;

  if( p->bIncr ){
    rc = fts3EvalIncrPhraseNext(pCsr, p, pbEof);
  }else if( pCsr->bDesc!=pTab->bDescIdx && pDL->nAll ){
    sqlite3Fts3DoclistPrev(pTab->bDescIdx, pDL->aAll, pDL->nAll, 
        &pDL->pNextDocid, &pDL->iDocid, &pDL->nList, pbEof
    );
    pDL->pList = pDL->pNextDocid;
  }else{
    fts3EvalDlPhraseNext(pTab, pDL, pbEof);
  }

  return rc;
}