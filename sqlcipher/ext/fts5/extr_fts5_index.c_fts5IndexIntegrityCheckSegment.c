#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  scalar_t__ i64 ;
struct TYPE_29__ {int iLeaf; } ;
struct TYPE_28__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; } ;
struct TYPE_27__ {scalar_t__ nn; scalar_t__ szLeaf; int /*<<< orphan*/ * p; } ;
struct TYPE_26__ {int rc; TYPE_4__* pConfig; } ;
struct TYPE_25__ {int pgnoFirst; int pgnoLast; int iSegid; } ;
typedef  TYPE_1__ Fts5StructureSegment ;
typedef  TYPE_2__ Fts5Index ;
typedef  int /*<<< orphan*/  Fts5DlidxIter ;
typedef  TYPE_3__ Fts5Data ;
typedef  TYPE_4__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_SZLEAF_OK (TYPE_3__*) ; 
 void* FTS5_CORRUPT ; 
 scalar_t__ FTS5_SEGMENT_ROWID (int,int) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 TYPE_3__* fts5DataRead (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_3__*) ; 
 scalar_t__ fts5DlidxIterEof (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5DlidxIterFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts5DlidxIterInit (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fts5DlidxIterNext (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int fts5DlidxIterPgno (int /*<<< orphan*/ *) ; 
 scalar_t__ fts5DlidxIterRowid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5GetVarint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fts5GetVarint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5IndexIntegrityCheckEmpty (TYPE_2__*,TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  fts5IndexPrepareStmt (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5IntegrityCheckPgidx (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ fts5LeafFirstRowidOff (TYPE_3__*) ; 
 int fts5LeafFirstTermOff (TYPE_3__*) ; 
 TYPE_3__* fts5LeafRead (TYPE_2__*,scalar_t__) ; 
 int fts5Memcmp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5TestDlidxReverse (TYPE_2__*,int,int) ; 
 TYPE_5__ iter ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5IndexIntegrityCheckSegment(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5StructureSegment *pSeg      /* Segment to check internal consistency */
){
  Fts5Config *pConfig = p->pConfig;
  sqlite3_stmt *pStmt = 0;
  int rc2;
  int iIdxPrevLeaf = pSeg->pgnoFirst-1;
  int iDlidxPrevLeaf = pSeg->pgnoLast;

  if( pSeg->pgnoFirst==0 ) return;

  fts5IndexPrepareStmt(p, &pStmt, sqlite3_mprintf(
      "SELECT segid, term, (pgno>>1), (pgno&1) FROM %Q.'%q_idx' WHERE segid=%d",
      pConfig->zDb, pConfig->zName, pSeg->iSegid
  ));

  /* Iterate through the b-tree hierarchy.  */
  while( p->rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pStmt) ){
    i64 iRow;                     /* Rowid for this leaf */
    Fts5Data *pLeaf;              /* Data for this leaf */

    int nIdxTerm = sqlite3_column_bytes(pStmt, 1);
    const char *zIdxTerm = (const char*)sqlite3_column_text(pStmt, 1);
    int iIdxLeaf = sqlite3_column_int(pStmt, 2);
    int bIdxDlidx = sqlite3_column_int(pStmt, 3);

    /* If the leaf in question has already been trimmed from the segment, 
    ** ignore this b-tree entry. Otherwise, load it into memory. */
    if( iIdxLeaf<pSeg->pgnoFirst ) continue;
    iRow = FTS5_SEGMENT_ROWID(pSeg->iSegid, iIdxLeaf);
    pLeaf = fts5LeafRead(p, iRow);
    if( pLeaf==0 ) break;

    /* Check that the leaf contains at least one term, and that it is equal
    ** to or larger than the split-key in zIdxTerm.  Also check that if there
    ** is also a rowid pointer within the leaf page header, it points to a
    ** location before the term.  */
    if( pLeaf->nn<=pLeaf->szLeaf ){
      p->rc = FTS5_CORRUPT;
    }else{
      int iOff;                   /* Offset of first term on leaf */
      int iRowidOff;              /* Offset of first rowid on leaf */
      int nTerm;                  /* Size of term on leaf in bytes */
      int res;                    /* Comparison of term and split-key */

      iOff = fts5LeafFirstTermOff(pLeaf);
      iRowidOff = fts5LeafFirstRowidOff(pLeaf);
      if( iRowidOff>=iOff || iOff>=pLeaf->szLeaf ){
        p->rc = FTS5_CORRUPT;
      }else{
        iOff += fts5GetVarint32(&pLeaf->p[iOff], nTerm);
        res = fts5Memcmp(&pLeaf->p[iOff], zIdxTerm, MIN(nTerm, nIdxTerm));
        if( res==0 ) res = nTerm - nIdxTerm;
        if( res<0 ) p->rc = FTS5_CORRUPT;
      }

      fts5IntegrityCheckPgidx(p, pLeaf);
    }
    fts5DataRelease(pLeaf);
    if( p->rc ) break;

    /* Now check that the iter.nEmpty leaves following the current leaf
    ** (a) exist and (b) contain no terms. */
    fts5IndexIntegrityCheckEmpty(
        p, pSeg, iIdxPrevLeaf+1, iDlidxPrevLeaf+1, iIdxLeaf-1
    );
    if( p->rc ) break;

    /* If there is a doclist-index, check that it looks right. */
    if( bIdxDlidx ){
      Fts5DlidxIter *pDlidx = 0;  /* For iterating through doclist index */
      int iPrevLeaf = iIdxLeaf;
      int iSegid = pSeg->iSegid;
      int iPg = 0;
      i64 iKey;

      for(pDlidx=fts5DlidxIterInit(p, 0, iSegid, iIdxLeaf);
          fts5DlidxIterEof(p, pDlidx)==0;
          fts5DlidxIterNext(p, pDlidx)
      ){

        /* Check any rowid-less pages that occur before the current leaf. */
        for(iPg=iPrevLeaf+1; iPg<fts5DlidxIterPgno(pDlidx); iPg++){
          iKey = FTS5_SEGMENT_ROWID(iSegid, iPg);
          pLeaf = fts5DataRead(p, iKey);
          if( pLeaf ){
            if( fts5LeafFirstRowidOff(pLeaf)!=0 ) p->rc = FTS5_CORRUPT;
            fts5DataRelease(pLeaf);
          }
        }
        iPrevLeaf = fts5DlidxIterPgno(pDlidx);

        /* Check that the leaf page indicated by the iterator really does
        ** contain the rowid suggested by the same. */
        iKey = FTS5_SEGMENT_ROWID(iSegid, iPrevLeaf);
        pLeaf = fts5DataRead(p, iKey);
        if( pLeaf ){
          i64 iRowid;
          int iRowidOff = fts5LeafFirstRowidOff(pLeaf);
          ASSERT_SZLEAF_OK(pLeaf);
          if( iRowidOff>=pLeaf->szLeaf ){
            p->rc = FTS5_CORRUPT;
          }else{
            fts5GetVarint(&pLeaf->p[iRowidOff], (u64*)&iRowid);
            if( iRowid!=fts5DlidxIterRowid(pDlidx) ) p->rc = FTS5_CORRUPT;
          }
          fts5DataRelease(pLeaf);
        }
      }

      iDlidxPrevLeaf = iPg;
      fts5DlidxIterFree(pDlidx);
      fts5TestDlidxReverse(p, iSegid, iIdxLeaf);
    }else{
      iDlidxPrevLeaf = pSeg->pgnoLast;
      /* TODO: Check there is no doclist index */
    }

    iIdxPrevLeaf = iIdxLeaf;
  }

  rc2 = sqlite3_finalize(pStmt);
  if( p->rc==SQLITE_OK ) p->rc = rc2;

  /* Page iter.iLeaf must now be the rightmost leaf-page in the segment */
#if 0
  if( p->rc==SQLITE_OK && iter.iLeaf!=pSeg->pgnoLast ){
    p->rc = FTS5_CORRUPT;
  }
#endif
}