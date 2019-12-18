#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sIter ;
struct TYPE_14__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_13__ {int iCol; int iPos; int hlmask; int covered; } ;
struct TYPE_12__ {int iCol; int nSnippet; int nPhrase; int iCurrent; struct TYPE_12__* aPhrase; scalar_t__ pHead; TYPE_4__* pCsr; } ;
typedef  TYPE_1__ SnippetPhrase ;
typedef  TYPE_1__ SnippetIter ;
typedef  TYPE_3__ SnippetFragment ;
typedef  TYPE_4__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3ExprIterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int fts3ExprLoadDoclists (TYPE_4__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts3SnippetDetails (TYPE_1__*,int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  fts3SnippetFindPositions ; 
 int /*<<< orphan*/  fts3SnippetNextCandidate (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts3BestSnippet(
  int nSnippet,                   /* Desired snippet length */
  Fts3Cursor *pCsr,               /* Cursor to create snippet for */
  int iCol,                       /* Index of column to create snippet from */
  u64 mCovered,                   /* Mask of phrases already covered */
  u64 *pmSeen,                    /* IN/OUT: Mask of phrases seen */
  SnippetFragment *pFragment,     /* OUT: Best snippet found */
  int *piScore                    /* OUT: Score of snippet pFragment */
){
  int rc;                         /* Return Code */
  int nList;                      /* Number of phrases in expression */
  SnippetIter sIter;              /* Iterates through snippet candidates */
  sqlite3_int64 nByte;            /* Number of bytes of space to allocate */
  int iBestScore = -1;            /* Best snippet score found so far */
  int i;                          /* Loop counter */

  memset(&sIter, 0, sizeof(sIter));

  /* Iterate through the phrases in the expression to count them. The same
  ** callback makes sure the doclists are loaded for each phrase.
  */
  rc = fts3ExprLoadDoclists(pCsr, &nList, 0);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  /* Now that it is known how many phrases there are, allocate and zero
  ** the required space using malloc().
  */
  nByte = sizeof(SnippetPhrase) * nList;
  sIter.aPhrase = (SnippetPhrase *)sqlite3_malloc64(nByte);
  if( !sIter.aPhrase ){
    return SQLITE_NOMEM;
  }
  memset(sIter.aPhrase, 0, nByte);

  /* Initialize the contents of the SnippetIter object. Then iterate through
  ** the set of phrases in the expression to populate the aPhrase[] array.
  */
  sIter.pCsr = pCsr;
  sIter.iCol = iCol;
  sIter.nSnippet = nSnippet;
  sIter.nPhrase = nList;
  sIter.iCurrent = -1;
  rc = fts3ExprIterate(pCsr->pExpr, fts3SnippetFindPositions, (void*)&sIter);
  if( rc==SQLITE_OK ){

    /* Set the *pmSeen output variable. */
    for(i=0; i<nList; i++){
      if( sIter.aPhrase[i].pHead ){
        *pmSeen |= (u64)1 << i;
      }
    }

    /* Loop through all candidate snippets. Store the best snippet in 
     ** *pFragment. Store its associated 'score' in iBestScore.
     */
    pFragment->iCol = iCol;
    while( !fts3SnippetNextCandidate(&sIter) ){
      int iPos;
      int iScore;
      u64 mCover;
      u64 mHighlite;
      fts3SnippetDetails(&sIter, mCovered, &iPos, &iScore, &mCover,&mHighlite);
      assert( iScore>=0 );
      if( iScore>iBestScore ){
        pFragment->iPos = iPos;
        pFragment->hlmask = mHighlite;
        pFragment->covered = mCover;
        iBestScore = iScore;
      }
    }

    *piScore = iBestScore;
  }
  sqlite3_free(sIter.aPhrase);
  return rc;
}