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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_6__ {int nSegment; TYPE_1__** apSegment; } ;
struct TYPE_5__ {int iIdx; scalar_t__ aNode; char* zTerm; int nTerm; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_1__ Fts3SegReader ;
typedef  TYPE_2__ Fts3MultiSegReader ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3DeleteSegment (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fts3RemoveSegdirEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int fts3RepackSegdirLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fts3TruncateSegment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,int) ; 

__attribute__((used)) static int fts3IncrmergeChomp(
  Fts3Table *p,                   /* FTS table handle */
  sqlite3_int64 iAbsLevel,        /* Absolute level containing segments */
  Fts3MultiSegReader *pCsr,       /* Chomp all segments opened by this cursor */
  int *pnRem                      /* Number of segments not deleted */
){
  int i;
  int nRem = 0;
  int rc = SQLITE_OK;

  for(i=pCsr->nSegment-1; i>=0 && rc==SQLITE_OK; i--){
    Fts3SegReader *pSeg = 0;
    int j;

    /* Find the Fts3SegReader object with Fts3SegReader.iIdx==i. It is hiding
    ** somewhere in the pCsr->apSegment[] array.  */
    for(j=0; ALWAYS(j<pCsr->nSegment); j++){
      pSeg = pCsr->apSegment[j];
      if( pSeg->iIdx==i ) break;
    }
    assert( j<pCsr->nSegment && pSeg->iIdx==i );

    if( pSeg->aNode==0 ){
      /* Seg-reader is at EOF. Remove the entire input segment. */
      rc = fts3DeleteSegment(p, pSeg);
      if( rc==SQLITE_OK ){
        rc = fts3RemoveSegdirEntry(p, iAbsLevel, pSeg->iIdx);
      }
      *pnRem = 0;
    }else{
      /* The incremental merge did not copy all the data from this 
      ** segment to the upper level. The segment is modified in place
      ** so that it contains no keys smaller than zTerm/nTerm. */ 
      const char *zTerm = pSeg->zTerm;
      int nTerm = pSeg->nTerm;
      rc = fts3TruncateSegment(p, iAbsLevel, pSeg->iIdx, zTerm, nTerm);
      nRem++;
    }
  }

  if( rc==SQLITE_OK && nRem!=pCsr->nSegment ){
    rc = fts3RepackSegdirLevel(p, iAbsLevel);
  }

  *pnRem = nRem;
  return rc;
}