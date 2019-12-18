#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ rc; } ;
struct TYPE_19__ {scalar_t__ iLeafPgno; int iLeafOffset; TYPE_16__* pLeaf; scalar_t__ iPgidxOff; TYPE_1__* pSeg; } ;
struct TYPE_18__ {scalar_t__ pgnoFirst; } ;
struct TYPE_17__ {int nn; scalar_t__ szLeaf; } ;
typedef  TYPE_1__ Fts5StructureSegment ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_nc (int) ; 
 int fts5LeafFirstTermOff (TYPE_16__*) ; 
 int /*<<< orphan*/  fts5SegIterLoadNPos (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5SegIterLoadTerm (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5SegIterNextPage (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5SegIterSetNext (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fts5SegIterInit(
  Fts5Index *p,                   /* FTS index object */
  Fts5StructureSegment *pSeg,     /* Description of segment */
  Fts5SegIter *pIter              /* Object to populate */
){
  if( pSeg->pgnoFirst==0 ){
    /* This happens if the segment is being used as an input to an incremental
    ** merge and all data has already been "trimmed". See function
    ** fts5TrimSegments() for details. In this case leave the iterator empty.
    ** The caller will see the (pIter->pLeaf==0) and assume the iterator is
    ** at EOF already. */
    assert( pIter->pLeaf==0 );
    return;
  }

  if( p->rc==SQLITE_OK ){
    memset(pIter, 0, sizeof(*pIter));
    fts5SegIterSetNext(p, pIter);
    pIter->pSeg = pSeg;
    pIter->iLeafPgno = pSeg->pgnoFirst-1;
    fts5SegIterNextPage(p, pIter);
  }

  if( p->rc==SQLITE_OK ){
    pIter->iLeafOffset = 4;
    assert_nc( pIter->pLeaf->nn>4 );
    assert_nc( fts5LeafFirstTermOff(pIter->pLeaf)==4 );
    pIter->iPgidxOff = pIter->pLeaf->szLeaf+1;
    fts5SegIterLoadTerm(p, pIter, 0);
    fts5SegIterLoadNPos(p, pIter);
  }
}