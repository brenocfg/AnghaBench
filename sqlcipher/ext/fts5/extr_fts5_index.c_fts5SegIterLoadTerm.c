#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int n; int nSpace; } ;
struct TYPE_11__ {int /*<<< orphan*/  rc; } ;
struct TYPE_10__ {int iLeafOffset; int iTermLeafOffset; size_t iPgidxOff; size_t iEndofDoclist; TYPE_1__* pLeaf; int /*<<< orphan*/  iLeafPgno; int /*<<< orphan*/  iTermLeafPgno; TYPE_8__ term; } ;
struct TYPE_9__ {int szLeaf; size_t nn; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_CORRUPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5BufferAppendBlob (int /*<<< orphan*/ *,TYPE_8__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fts5GetVarint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5SegIterLoadRowid (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void fts5SegIterLoadTerm(Fts5Index *p, Fts5SegIter *pIter, int nKeep){
  u8 *a = pIter->pLeaf->p;        /* Buffer to read data from */
  int iOff = pIter->iLeafOffset;  /* Offset to read at */
  int nNew;                       /* Bytes of new data */

  iOff += fts5GetVarint32(&a[iOff], nNew);
  if( iOff+nNew>pIter->pLeaf->szLeaf || nKeep>pIter->term.n || nNew==0 ){
    p->rc = FTS5_CORRUPT;
    return;
  }
  pIter->term.n = nKeep;
  fts5BufferAppendBlob(&p->rc, &pIter->term, nNew, &a[iOff]);
  assert( pIter->term.n<=pIter->term.nSpace );
  iOff += nNew;
  pIter->iTermLeafOffset = iOff;
  pIter->iTermLeafPgno = pIter->iLeafPgno;
  pIter->iLeafOffset = iOff;

  if( pIter->iPgidxOff>=pIter->pLeaf->nn ){
    pIter->iEndofDoclist = pIter->pLeaf->nn+1;
  }else{
    int nExtra;
    pIter->iPgidxOff += fts5GetVarint32(&a[pIter->iPgidxOff], nExtra);
    pIter->iEndofDoclist += nExtra;
  }

  fts5SegIterLoadRowid(p, pIter);
}