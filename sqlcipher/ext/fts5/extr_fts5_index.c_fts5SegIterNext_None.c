#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ i64 ;
struct TYPE_18__ {scalar_t__ rc; int /*<<< orphan*/  pHash; TYPE_1__* pConfig; } ;
struct TYPE_17__ {int flags; int iLeafOffset; int iEndofDoclist; TYPE_12__* pLeaf; scalar_t__ iRowid; int /*<<< orphan*/  term; scalar_t__ pSeg; } ;
struct TYPE_16__ {scalar_t__ eDetail; } ;
struct TYPE_15__ {int szLeaf; int nn; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_SZLEAF_OK (TYPE_12__*) ; 
 scalar_t__ FTS5_DETAIL_NONE ; 
 int FTS5_SEGITER_ONETERM ; 
 int FTS5_SEGITER_REVERSE ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_12__*) ; 
 int fts5GetVarint (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ fts5GetVarint32 (int /*<<< orphan*/ *,int) ; 
 int fts5LeafFirstTermOff (TYPE_12__*) ; 
 int /*<<< orphan*/  fts5SegIterLoadNPos (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5SegIterLoadTerm (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  fts5SegIterNextPage (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferSet (scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3Fts5GetVarint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3Fts5HashScanEntry (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  sqlite3Fts5HashScanNext (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void fts5SegIterNext_None(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5SegIter *pIter,             /* Iterator to advance */
  int *pbNewTerm                  /* OUT: Set for new term */
){
  int iOff;

  assert( p->rc==SQLITE_OK );
  assert( (pIter->flags & FTS5_SEGITER_REVERSE)==0 );
  assert( p->pConfig->eDetail==FTS5_DETAIL_NONE );

  ASSERT_SZLEAF_OK(pIter->pLeaf);
  iOff = pIter->iLeafOffset;

  /* Next entry is on the next page */
  if( pIter->pSeg && iOff>=pIter->pLeaf->szLeaf ){
    fts5SegIterNextPage(p, pIter);
    if( p->rc || pIter->pLeaf==0 ) return;
    pIter->iRowid = 0;
    iOff = 4;
  }

  if( iOff<pIter->iEndofDoclist ){
    /* Next entry is on the current page */
    i64 iDelta;
    iOff += sqlite3Fts5GetVarint(&pIter->pLeaf->p[iOff], (u64*)&iDelta);
    pIter->iLeafOffset = iOff;
    pIter->iRowid += iDelta;
  }else if( (pIter->flags & FTS5_SEGITER_ONETERM)==0 ){
    if( pIter->pSeg ){
      int nKeep = 0;
      if( iOff!=fts5LeafFirstTermOff(pIter->pLeaf) ){
        iOff += fts5GetVarint32(&pIter->pLeaf->p[iOff], nKeep);
      }
      pIter->iLeafOffset = iOff;
      fts5SegIterLoadTerm(p, pIter, nKeep);
    }else{
      const u8 *pList = 0;
      const char *zTerm = 0;
      int nList;
      sqlite3Fts5HashScanNext(p->pHash);
      sqlite3Fts5HashScanEntry(p->pHash, &zTerm, &pList, &nList);
      if( pList==0 ) goto next_none_eof;
      pIter->pLeaf->p = (u8*)pList;
      pIter->pLeaf->nn = nList;
      pIter->pLeaf->szLeaf = nList;
      pIter->iEndofDoclist = nList;
      sqlite3Fts5BufferSet(&p->rc,&pIter->term, (int)strlen(zTerm), (u8*)zTerm);
      pIter->iLeafOffset = fts5GetVarint(pList, (u64*)&pIter->iRowid);
    }

    if( pbNewTerm ) *pbNewTerm = 1;
  }else{
    goto next_none_eof;
  }

  fts5SegIterLoadNPos(p, pIter);

  return;
 next_none_eof:
  fts5DataRelease(pIter->pLeaf);
  pIter->pLeaf = 0;
}