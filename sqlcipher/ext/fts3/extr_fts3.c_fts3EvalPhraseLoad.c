#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pVtab; } ;
struct TYPE_12__ {TYPE_1__ base; } ;
struct TYPE_11__ {int nToken; int /*<<< orphan*/  iColumn; TYPE_2__* aToken; } ;
struct TYPE_10__ {scalar_t__ pDeferred; scalar_t__ pSegcsr; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_2__ Fts3PhraseToken ;
typedef  TYPE_3__ Fts3Phrase ;
typedef  TYPE_4__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3EvalPhraseMergeToken (int /*<<< orphan*/ *,TYPE_3__*,int,char*,int) ; 
 int fts3TermSelect (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int*,char**) ; 

__attribute__((used)) static int fts3EvalPhraseLoad(
  Fts3Cursor *pCsr,               /* FTS Cursor handle */
  Fts3Phrase *p                   /* Phrase object */
){
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  int iToken;
  int rc = SQLITE_OK;

  for(iToken=0; rc==SQLITE_OK && iToken<p->nToken; iToken++){
    Fts3PhraseToken *pToken = &p->aToken[iToken];
    assert( pToken->pDeferred==0 || pToken->pSegcsr==0 );

    if( pToken->pSegcsr ){
      int nThis = 0;
      char *pThis = 0;
      rc = fts3TermSelect(pTab, pToken, p->iColumn, &nThis, &pThis);
      if( rc==SQLITE_OK ){
        rc = fts3EvalPhraseMergeToken(pTab, p, iToken, pThis, nThis);
      }
    }
    assert( pToken->pSegcsr==0 );
  }

  return rc;
}