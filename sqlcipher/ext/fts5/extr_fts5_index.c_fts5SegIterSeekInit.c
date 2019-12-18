#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int i64 ;
struct TYPE_21__ {int /*<<< orphan*/  rc; } ;
struct TYPE_20__ {int iLeafPgno; scalar_t__ pLeaf; int /*<<< orphan*/  term; int /*<<< orphan*/  flags; TYPE_1__* pSeg; } ;
struct TYPE_19__ {int pgnoFirst; int /*<<< orphan*/  iSegid; } ;
typedef  TYPE_1__ Fts5StructureSegment ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 int FTS5INDEX_QUERY_DESC ; 
 int FTS5INDEX_QUERY_SCAN ; 
 int /*<<< orphan*/  FTS5_SEGITER_ONETERM ; 
 int /*<<< orphan*/  FTS5_SEGITER_REVERSE ; 
 int /*<<< orphan*/  SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_nc (int) ; 
 scalar_t__ fts5BufferCompareBlob (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * fts5IdxSelectStmt (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5LeafSeek (TYPE_3__*,int,TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  fts5SegIterLoadDlidx (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5SegIterNextPage (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5SegIterReverse (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5SegIterSetNext (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5SegIterSeekInit(
  Fts5Index *p,                   /* FTS5 backend */
  const u8 *pTerm, int nTerm,     /* Term to seek to */
  int flags,                      /* Mask of FTS5INDEX_XXX flags */
  Fts5StructureSegment *pSeg,     /* Description of segment */
  Fts5SegIter *pIter              /* Object to populate */
){
  int iPg = 1;
  int bGe = (flags & FTS5INDEX_QUERY_SCAN);
  int bDlidx = 0;                 /* True if there is a doclist-index */
  sqlite3_stmt *pIdxSelect = 0;

  assert( bGe==0 || (flags & FTS5INDEX_QUERY_DESC)==0 );
  assert( pTerm && nTerm );
  memset(pIter, 0, sizeof(*pIter));
  pIter->pSeg = pSeg;

  /* This block sets stack variable iPg to the leaf page number that may
  ** contain term (pTerm/nTerm), if it is present in the segment. */
  pIdxSelect = fts5IdxSelectStmt(p);
  if( p->rc ) return;
  sqlite3_bind_int(pIdxSelect, 1, pSeg->iSegid);
  sqlite3_bind_blob(pIdxSelect, 2, pTerm, nTerm, SQLITE_STATIC);
  if( SQLITE_ROW==sqlite3_step(pIdxSelect) ){
    i64 val = sqlite3_column_int(pIdxSelect, 0);
    iPg = (int)(val>>1);
    bDlidx = (val & 0x0001);
  }
  p->rc = sqlite3_reset(pIdxSelect);
  sqlite3_bind_null(pIdxSelect, 2);

  if( iPg<pSeg->pgnoFirst ){
    iPg = pSeg->pgnoFirst;
    bDlidx = 0;
  }

  pIter->iLeafPgno = iPg - 1;
  fts5SegIterNextPage(p, pIter);

  if( pIter->pLeaf ){
    fts5LeafSeek(p, bGe, pIter, pTerm, nTerm);
  }

  if( p->rc==SQLITE_OK && bGe==0 ){
    pIter->flags |= FTS5_SEGITER_ONETERM;
    if( pIter->pLeaf ){
      if( flags & FTS5INDEX_QUERY_DESC ){
        pIter->flags |= FTS5_SEGITER_REVERSE;
      }
      if( bDlidx ){
        fts5SegIterLoadDlidx(p, pIter);
      }
      if( flags & FTS5INDEX_QUERY_DESC ){
        fts5SegIterReverse(p, pIter);
      }
    }
  }

  fts5SegIterSetNext(p, pIter);

  /* Either:
  **
  **   1) an error has occurred, or
  **   2) the iterator points to EOF, or
  **   3) the iterator points to an entry with term (pTerm/nTerm), or
  **   4) the FTS5INDEX_QUERY_SCAN flag was set and the iterator points
  **      to an entry with a term greater than or equal to (pTerm/nTerm).
  */
  assert_nc( p->rc!=SQLITE_OK                                       /* 1 */
   || pIter->pLeaf==0                                               /* 2 */
   || fts5BufferCompareBlob(&pIter->term, pTerm, nTerm)==0          /* 3 */
   || (bGe && fts5BufferCompareBlob(&pIter->term, pTerm, nTerm)>0)  /* 4 */
  );
}