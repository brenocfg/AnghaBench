#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  aStatic ;
struct TYPE_20__ {scalar_t__ n; int /*<<< orphan*/  p; } ;
struct TYPE_19__ {int nPhrase; scalar_t__ nNear; TYPE_4__** apPhrase; } ;
struct TYPE_18__ {scalar_t__ nTerm; TYPE_6__ poslist; } ;
struct TYPE_17__ {scalar_t__ iPos; scalar_t__ iLookahead; } ;
struct TYPE_15__ {scalar_t__ iPrev; } ;
struct TYPE_16__ {TYPE_6__* pOut; TYPE_3__ reader; TYPE_1__ writer; } ;
typedef  TYPE_1__ Fts5PoslistWriter ;
typedef  TYPE_2__ Fts5NearTrimmer ;
typedef  TYPE_3__ Fts5LookaheadReader ;
typedef  TYPE_4__ Fts5ExprPhrase ;
typedef  TYPE_5__ Fts5ExprNearset ;
typedef  TYPE_6__ Fts5Buffer ;

/* Variables and functions */
 int ArraySize (TYPE_2__*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5LookaheadReaderInit (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 scalar_t__ fts5LookaheadReaderNext (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5PoslistWriterAppend (TYPE_6__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static int fts5ExprNearIsMatch(int *pRc, Fts5ExprNearset *pNear){
  Fts5NearTrimmer aStatic[4];
  Fts5NearTrimmer *a = aStatic;
  Fts5ExprPhrase **apPhrase = pNear->apPhrase;

  int i;
  int rc = *pRc;
  int bMatch;

  assert( pNear->nPhrase>1 );

  /* If the aStatic[] array is not large enough, allocate a large array
  ** using sqlite3_malloc(). This approach could be improved upon. */
  if( pNear->nPhrase>ArraySize(aStatic) ){
    sqlite3_int64 nByte = sizeof(Fts5NearTrimmer) * pNear->nPhrase;
    a = (Fts5NearTrimmer*)sqlite3Fts5MallocZero(&rc, nByte);
  }else{
    memset(aStatic, 0, sizeof(aStatic));
  }
  if( rc!=SQLITE_OK ){
    *pRc = rc;
    return 0;
  }

  /* Initialize a lookahead iterator for each phrase. After passing the
  ** buffer and buffer size to the lookaside-reader init function, zero
  ** the phrase poslist buffer. The new poslist for the phrase (containing
  ** the same entries as the original with some entries removed on account 
  ** of the NEAR constraint) is written over the original even as it is
  ** being read. This is safe as the entries for the new poslist are a
  ** subset of the old, so it is not possible for data yet to be read to
  ** be overwritten.  */
  for(i=0; i<pNear->nPhrase; i++){
    Fts5Buffer *pPoslist = &apPhrase[i]->poslist;
    fts5LookaheadReaderInit(pPoslist->p, pPoslist->n, &a[i].reader);
    pPoslist->n = 0;
    a[i].pOut = pPoslist;
  }

  while( 1 ){
    int iAdv;
    i64 iMin;
    i64 iMax;

    /* This block advances the phrase iterators until they point to a set of
    ** entries that together comprise a match.  */
    iMax = a[0].reader.iPos;
    do {
      bMatch = 1;
      for(i=0; i<pNear->nPhrase; i++){
        Fts5LookaheadReader *pPos = &a[i].reader;
        iMin = iMax - pNear->apPhrase[i]->nTerm - pNear->nNear;
        if( pPos->iPos<iMin || pPos->iPos>iMax ){
          bMatch = 0;
          while( pPos->iPos<iMin ){
            if( fts5LookaheadReaderNext(pPos) ) goto ismatch_out;
          }
          if( pPos->iPos>iMax ) iMax = pPos->iPos;
        }
      }
    }while( bMatch==0 );

    /* Add an entry to each output position list */
    for(i=0; i<pNear->nPhrase; i++){
      i64 iPos = a[i].reader.iPos;
      Fts5PoslistWriter *pWriter = &a[i].writer;
      if( a[i].pOut->n==0 || iPos!=pWriter->iPrev ){
        sqlite3Fts5PoslistWriterAppend(a[i].pOut, pWriter, iPos);
      }
    }

    iAdv = 0;
    iMin = a[0].reader.iLookahead;
    for(i=0; i<pNear->nPhrase; i++){
      if( a[i].reader.iLookahead < iMin ){
        iMin = a[i].reader.iLookahead;
        iAdv = i;
      }
    }
    if( fts5LookaheadReaderNext(&a[iAdv].reader) ) goto ismatch_out;
  }

  ismatch_out: {
    int bRet = a[0].pOut->n>0;
    *pRc = rc;
    if( a!=aStatic ) sqlite3_free(a);
    return bRet;
  }
}