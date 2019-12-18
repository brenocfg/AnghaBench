#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ iCurrent; int nPhrase; int nSnippet; TYPE_1__* aPhrase; } ;
struct TYPE_4__ {int iHead; int iTail; scalar_t__ pTail; scalar_t__ pHead; } ;
typedef  TYPE_1__ SnippetPhrase ;
typedef  TYPE_2__ SnippetIter ;

/* Variables and functions */
 int /*<<< orphan*/  fts3SnippetAdvance (scalar_t__*,int*,int) ; 

__attribute__((used)) static int fts3SnippetNextCandidate(SnippetIter *pIter){
  int i;                          /* Loop counter */

  if( pIter->iCurrent<0 ){
    /* The SnippetIter object has just been initialized. The first snippet
    ** candidate always starts at offset 0 (even if this candidate has a
    ** score of 0.0).
    */
    pIter->iCurrent = 0;

    /* Advance the 'head' iterator of each phrase to the first offset that
    ** is greater than or equal to (iNext+nSnippet).
    */
    for(i=0; i<pIter->nPhrase; i++){
      SnippetPhrase *pPhrase = &pIter->aPhrase[i];
      fts3SnippetAdvance(&pPhrase->pHead, &pPhrase->iHead, pIter->nSnippet);
    }
  }else{
    int iStart;
    int iEnd = 0x7FFFFFFF;

    for(i=0; i<pIter->nPhrase; i++){
      SnippetPhrase *pPhrase = &pIter->aPhrase[i];
      if( pPhrase->pHead && pPhrase->iHead<iEnd ){
        iEnd = pPhrase->iHead;
      }
    }
    if( iEnd==0x7FFFFFFF ){
      return 1;
    }

    pIter->iCurrent = iStart = iEnd - pIter->nSnippet + 1;
    for(i=0; i<pIter->nPhrase; i++){
      SnippetPhrase *pPhrase = &pIter->aPhrase[i];
      fts3SnippetAdvance(&pPhrase->pHead, &pPhrase->iHead, iEnd+1);
      fts3SnippetAdvance(&pPhrase->pTail, &pPhrase->iTail, iStart);
    }
  }

  return 0;
}