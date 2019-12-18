#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int bIgnore; int /*<<< orphan*/  pList; int /*<<< orphan*/  nList; int /*<<< orphan*/  iDocid; } ;
typedef  TYPE_1__ TokenDoclist ;
struct TYPE_10__ {int /*<<< orphan*/  iDocid; int /*<<< orphan*/  nList; int /*<<< orphan*/  pList; } ;
struct TYPE_9__ {int iDoclistToken; TYPE_2__* aToken; TYPE_6__ doclist; } ;
struct TYPE_8__ {scalar_t__ pSegcsr; scalar_t__ pDeferred; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_2__ Fts3PhraseToken ;
typedef  TYPE_3__ Fts3Phrase ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3EvalDlPhraseNext (int /*<<< orphan*/ *,TYPE_6__*,int*) ; 
 int sqlite3Fts3MsrIncrNext (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int incrPhraseTokenNext(
  Fts3Table *pTab,                /* Virtual table handle */
  Fts3Phrase *pPhrase,            /* Phrase to advance token of */
  int iToken,                     /* Specific token to advance */
  TokenDoclist *p,                /* OUT: Docid and doclist for new entry */
  u8 *pbEof                       /* OUT: True if iterator is at EOF */
){
  int rc = SQLITE_OK;

  if( pPhrase->iDoclistToken==iToken ){
    assert( p->bIgnore==0 );
    assert( pPhrase->aToken[iToken].pSegcsr==0 );
    fts3EvalDlPhraseNext(pTab, &pPhrase->doclist, pbEof);
    p->pList = pPhrase->doclist.pList;
    p->nList = pPhrase->doclist.nList;
    p->iDocid = pPhrase->doclist.iDocid;
  }else{
    Fts3PhraseToken *pToken = &pPhrase->aToken[iToken];
    assert( pToken->pDeferred==0 );
    assert( pToken->pSegcsr || pPhrase->iDoclistToken>=0 );
    if( pToken->pSegcsr ){
      assert( p->bIgnore==0 );
      rc = sqlite3Fts3MsrIncrNext(
          pTab, pToken->pSegcsr, &p->iDocid, &p->pList, &p->nList
      );
      if( p->pList==0 ) *pbEof = 1;
    }else{
      p->bIgnore = 1;
    }
  }

  return rc;
}