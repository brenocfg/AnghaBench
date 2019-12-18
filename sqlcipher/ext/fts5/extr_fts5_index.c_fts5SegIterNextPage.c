#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t szLeaf; int /*<<< orphan*/ * p; scalar_t__ nn; } ;
struct TYPE_9__ {scalar_t__ iLeafPgno; size_t iPgidxOff; scalar_t__ iEndofDoclist; TYPE_3__* pLeaf; TYPE_3__* pNextLeaf; TYPE_1__* pSeg; } ;
struct TYPE_8__ {scalar_t__ pgnoLast; int /*<<< orphan*/  iSegid; } ;
typedef  TYPE_1__ Fts5StructureSegment ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  int /*<<< orphan*/  Fts5Index ;
typedef  TYPE_3__ Fts5Data ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_SEGMENT_ROWID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_3__*) ; 
 scalar_t__ fts5GetVarint32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fts5LeafIsTermless (TYPE_3__*) ; 
 TYPE_3__* fts5LeafRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5SegIterNextPage(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5SegIter *pIter              /* Iterator to advance to next page */
){
  Fts5Data *pLeaf;
  Fts5StructureSegment *pSeg = pIter->pSeg;
  fts5DataRelease(pIter->pLeaf);
  pIter->iLeafPgno++;
  if( pIter->pNextLeaf ){
    pIter->pLeaf = pIter->pNextLeaf;
    pIter->pNextLeaf = 0;
  }else if( pIter->iLeafPgno<=pSeg->pgnoLast ){
    pIter->pLeaf = fts5LeafRead(p, 
        FTS5_SEGMENT_ROWID(pSeg->iSegid, pIter->iLeafPgno)
    );
  }else{
    pIter->pLeaf = 0;
  }
  pLeaf = pIter->pLeaf;

  if( pLeaf ){
    pIter->iPgidxOff = pLeaf->szLeaf;
    if( fts5LeafIsTermless(pLeaf) ){
      pIter->iEndofDoclist = pLeaf->nn+1;
    }else{
      pIter->iPgidxOff += fts5GetVarint32(&pLeaf->p[pIter->iPgidxOff],
          pIter->iEndofDoclist
      );
    }
  }
}