#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  aHdr ;
struct TYPE_27__ {int n; int /*<<< orphan*/ * p; } ;
struct TYPE_26__ {int szLeaf; size_t nn; int* p; } ;
struct TYPE_25__ {scalar_t__ rc; } ;
struct TYPE_24__ {int nSeg; TYPE_3__* aSeg; } ;
struct TYPE_21__ {int n; int* p; } ;
struct TYPE_23__ {scalar_t__ pLeaf; int iTermLeafOffset; int iTermLeafPgno; int iLeafPgno; int iEndofDoclist; size_t iPgidxOff; TYPE_2__* pSeg; TYPE_1__ term; } ;
struct TYPE_22__ {int pgnoFirst; int iSegid; scalar_t__ pgnoLast; } ;
typedef  TYPE_3__ Fts5SegIter ;
typedef  TYPE_4__ Fts5Iter ;
typedef  TYPE_5__ Fts5Index ;
typedef  TYPE_6__ Fts5Data ;
typedef  TYPE_7__ Fts5Buffer ;

/* Variables and functions */
 scalar_t__ FTS5_CORRUPT ; 
 int /*<<< orphan*/  FTS5_SEGMENT_ROWID (int,int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  fts5BufferAppendBlob (scalar_t__*,TYPE_7__*,int,int*) ; 
 int /*<<< orphan*/  fts5BufferAppendVarint (scalar_t__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  fts5BufferFree (TYPE_7__*) ; 
 int /*<<< orphan*/  fts5BufferGrow (scalar_t__*,TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  fts5BufferZero (TYPE_7__*) ; 
 int /*<<< orphan*/  fts5DataDelete (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_6__*) ; 
 int /*<<< orphan*/  fts5DataWrite (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_6__* fts5LeafRead (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5PutU16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fts5TrimSegments(Fts5Index *p, Fts5Iter *pIter){
  int i;
  Fts5Buffer buf;
  memset(&buf, 0, sizeof(Fts5Buffer));
  for(i=0; i<pIter->nSeg && p->rc==SQLITE_OK; i++){
    Fts5SegIter *pSeg = &pIter->aSeg[i];
    if( pSeg->pSeg==0 ){
      /* no-op */
    }else if( pSeg->pLeaf==0 ){
      /* All keys from this input segment have been transfered to the output.
      ** Set both the first and last page-numbers to 0 to indicate that the
      ** segment is now empty. */
      pSeg->pSeg->pgnoLast = 0;
      pSeg->pSeg->pgnoFirst = 0;
    }else{
      int iOff = pSeg->iTermLeafOffset;     /* Offset on new first leaf page */
      i64 iLeafRowid;
      Fts5Data *pData;
      int iId = pSeg->pSeg->iSegid;
      u8 aHdr[4] = {0x00, 0x00, 0x00, 0x00};

      iLeafRowid = FTS5_SEGMENT_ROWID(iId, pSeg->iTermLeafPgno);
      pData = fts5LeafRead(p, iLeafRowid);
      if( pData ){
        if( iOff>pData->szLeaf ){
          /* This can occur if the pages that the segments occupy overlap - if
          ** a single page has been assigned to more than one segment. In
          ** this case a prior iteration of this loop may have corrupted the
          ** segment currently being trimmed.  */
          p->rc = FTS5_CORRUPT;
        }else{
          fts5BufferZero(&buf);
          fts5BufferGrow(&p->rc, &buf, pData->nn);
          fts5BufferAppendBlob(&p->rc, &buf, sizeof(aHdr), aHdr);
          fts5BufferAppendVarint(&p->rc, &buf, pSeg->term.n);
          fts5BufferAppendBlob(&p->rc, &buf, pSeg->term.n, pSeg->term.p);
          fts5BufferAppendBlob(&p->rc, &buf, pData->szLeaf-iOff,&pData->p[iOff]);
          if( p->rc==SQLITE_OK ){
            /* Set the szLeaf field */
            fts5PutU16(&buf.p[2], (u16)buf.n);
          }

          /* Set up the new page-index array */
          fts5BufferAppendVarint(&p->rc, &buf, 4);
          if( pSeg->iLeafPgno==pSeg->iTermLeafPgno 
           && pSeg->iEndofDoclist<pData->szLeaf
           && pSeg->iPgidxOff<=pData->nn
          ){
            int nDiff = pData->szLeaf - pSeg->iEndofDoclist;
            fts5BufferAppendVarint(&p->rc, &buf, buf.n - 1 - nDiff - 4);
            fts5BufferAppendBlob(&p->rc, &buf, 
                pData->nn - pSeg->iPgidxOff, &pData->p[pSeg->iPgidxOff]
            );
          }

          pSeg->pSeg->pgnoFirst = pSeg->iTermLeafPgno;
          fts5DataDelete(p, FTS5_SEGMENT_ROWID(iId, 1), iLeafRowid);
          fts5DataWrite(p, iLeafRowid, buf.p, buf.n);
        }
        fts5DataRelease(pData);
      }
    }
  }
  fts5BufferFree(&buf);
}