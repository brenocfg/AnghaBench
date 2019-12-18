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
typedef  int u64 ;
struct TYPE_5__ {int iCurrent; int nPhrase; int nSnippet; TYPE_1__* aPhrase; } ;
struct TYPE_4__ {char* pTail; int iTail; int nToken; } ;
typedef  TYPE_1__ SnippetPhrase ;
typedef  TYPE_2__ SnippetIter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3GetDeltaPosition (char**,int*) ; 

__attribute__((used)) static void fts3SnippetDetails(
  SnippetIter *pIter,             /* Snippet iterator */
  u64 mCovered,                   /* Bitmask of phrases already covered */
  int *piToken,                   /* OUT: First token of proposed snippet */
  int *piScore,                   /* OUT: "Score" for this snippet */
  u64 *pmCover,                   /* OUT: Bitmask of phrases covered */
  u64 *pmHighlight                /* OUT: Bitmask of terms to highlight */
){
  int iStart = pIter->iCurrent;   /* First token of snippet */
  int iScore = 0;                 /* Score of this snippet */
  int i;                          /* Loop counter */
  u64 mCover = 0;                 /* Mask of phrases covered by this snippet */
  u64 mHighlight = 0;             /* Mask of tokens to highlight in snippet */

  for(i=0; i<pIter->nPhrase; i++){
    SnippetPhrase *pPhrase = &pIter->aPhrase[i];
    if( pPhrase->pTail ){
      char *pCsr = pPhrase->pTail;
      int iCsr = pPhrase->iTail;

      while( iCsr<(iStart+pIter->nSnippet) && iCsr>=iStart ){
        int j;
        u64 mPhrase = (u64)1 << i;
        u64 mPos = (u64)1 << (iCsr - iStart);
        assert( iCsr>=iStart && (iCsr - iStart)<=64 );
        assert( i>=0 && i<=64 );
        if( (mCover|mCovered)&mPhrase ){
          iScore++;
        }else{
          iScore += 1000;
        }
        mCover |= mPhrase;

        for(j=0; j<pPhrase->nToken; j++){
          mHighlight |= (mPos>>j);
        }

        if( 0==(*pCsr & 0x0FE) ) break;
        fts3GetDeltaPosition(&pCsr, &iCsr);
      }
    }
  }

  /* Set the output variables before returning. */
  *piToken = iStart;
  *piScore = iScore;
  *pmCover = mCover;
  *pmHighlight = mHighlight;
}