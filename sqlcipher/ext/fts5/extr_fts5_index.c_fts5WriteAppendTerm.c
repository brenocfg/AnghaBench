#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_26__ {scalar_t__ n; int /*<<< orphan*/ * p; } ;
struct TYPE_25__ {scalar_t__ rc; TYPE_1__* pConfig; } ;
struct TYPE_18__ {int /*<<< orphan*/  p; scalar_t__ n; } ;
struct TYPE_19__ {int n; } ;
struct TYPE_24__ {int iPrevPgidx; int pgno; TYPE_14__ term; TYPE_15__ buf; TYPE_7__ pgidx; } ;
struct TYPE_23__ {int bFirstRowidInDoclist; scalar_t__ nDlidx; TYPE_3__* aDlidx; scalar_t__ bFirstRowidInPage; scalar_t__ bFirstTermInPage; TYPE_5__ writer; } ;
struct TYPE_21__ {scalar_t__ n; } ;
struct TYPE_22__ {int pgno; TYPE_2__ buf; } ;
struct TYPE_20__ {scalar_t__ pgsz; } ;
typedef  TYPE_4__ Fts5SegWriter ;
typedef  TYPE_5__ Fts5PageWriter ;
typedef  TYPE_6__ Fts5Index ;
typedef  TYPE_7__ Fts5Buffer ;

/* Variables and functions */
 scalar_t__ FTS5_DATA_PADDING ; 
 int MIN (scalar_t__,int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5BufferAppendBlob (scalar_t__*,TYPE_15__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5BufferAppendVarint (scalar_t__*,TYPE_15__*,int) ; 
 int /*<<< orphan*/  fts5BufferGrow (scalar_t__*,TYPE_15__*,scalar_t__) ; 
 int /*<<< orphan*/  fts5BufferSet (scalar_t__*,TYPE_14__*,int,int /*<<< orphan*/  const*) ; 
 int fts5PrefixCompress (int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5PutU16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5WriteBtreeTerm (TYPE_6__*,TYPE_4__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5WriteFlushLeaf (TYPE_6__*,TYPE_4__*) ; 
 scalar_t__ sqlite3Fts5PutVarint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fts5WriteAppendTerm(
  Fts5Index *p, 
  Fts5SegWriter *pWriter,
  int nTerm, const u8 *pTerm 
){
  int nPrefix;                    /* Bytes of prefix compression for term */
  Fts5PageWriter *pPage = &pWriter->writer;
  Fts5Buffer *pPgidx = &pWriter->writer.pgidx;
  int nMin = MIN(pPage->term.n, nTerm);

  assert( p->rc==SQLITE_OK );
  assert( pPage->buf.n>=4 );
  assert( pPage->buf.n>4 || pWriter->bFirstTermInPage );

  /* If the current leaf page is full, flush it to disk. */
  if( (pPage->buf.n + pPgidx->n + nTerm + 2)>=p->pConfig->pgsz ){
    if( pPage->buf.n>4 ){
      fts5WriteFlushLeaf(p, pWriter);
      if( p->rc!=SQLITE_OK ) return;
    }
    fts5BufferGrow(&p->rc, &pPage->buf, nTerm+FTS5_DATA_PADDING);
  }
  
  /* TODO1: Updating pgidx here. */
  pPgidx->n += sqlite3Fts5PutVarint(
      &pPgidx->p[pPgidx->n], pPage->buf.n - pPage->iPrevPgidx
  );
  pPage->iPrevPgidx = pPage->buf.n;
#if 0
  fts5PutU16(&pPgidx->p[pPgidx->n], pPage->buf.n);
  pPgidx->n += 2;
#endif

  if( pWriter->bFirstTermInPage ){
    nPrefix = 0;
    if( pPage->pgno!=1 ){
      /* This is the first term on a leaf that is not the leftmost leaf in
      ** the segment b-tree. In this case it is necessary to add a term to
      ** the b-tree hierarchy that is (a) larger than the largest term 
      ** already written to the segment and (b) smaller than or equal to
      ** this term. In other words, a prefix of (pTerm/nTerm) that is one
      ** byte longer than the longest prefix (pTerm/nTerm) shares with the
      ** previous term. 
      **
      ** Usually, the previous term is available in pPage->term. The exception
      ** is if this is the first term written in an incremental-merge step.
      ** In this case the previous term is not available, so just write a
      ** copy of (pTerm/nTerm) into the parent node. This is slightly
      ** inefficient, but still correct.  */
      int n = nTerm;
      if( pPage->term.n ){
        n = 1 + fts5PrefixCompress(nMin, pPage->term.p, pTerm);
      }
      fts5WriteBtreeTerm(p, pWriter, n, pTerm);
      if( p->rc!=SQLITE_OK ) return;
      pPage = &pWriter->writer;
    }
  }else{
    nPrefix = fts5PrefixCompress(nMin, pPage->term.p, pTerm);
    fts5BufferAppendVarint(&p->rc, &pPage->buf, nPrefix);
  }

  /* Append the number of bytes of new data, then the term data itself
  ** to the page. */
  fts5BufferAppendVarint(&p->rc, &pPage->buf, nTerm - nPrefix);
  fts5BufferAppendBlob(&p->rc, &pPage->buf, nTerm - nPrefix, &pTerm[nPrefix]);

  /* Update the Fts5PageWriter.term field. */
  fts5BufferSet(&p->rc, &pPage->term, nTerm, pTerm);
  pWriter->bFirstTermInPage = 0;

  pWriter->bFirstRowidInPage = 0;
  pWriter->bFirstRowidInDoclist = 1;

  assert( p->rc || (pWriter->nDlidx>0 && pWriter->aDlidx[0].buf.n==0) );
  pWriter->aDlidx[0].pgno = pPage->pgno;
}