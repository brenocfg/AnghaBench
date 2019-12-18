#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_42__ {scalar_t__ rc; scalar_t__ pHash; } ;
struct TYPE_36__ {scalar_t__ bEof; } ;
struct TYPE_41__ {int bRev; int bSkipEmpty; int nSeg; int /*<<< orphan*/  (* xSetOutputs ) (TYPE_6__*,TYPE_5__*) ;TYPE_2__* aFirst; TYPE_5__* aSeg; TYPE_1__ base; int /*<<< orphan*/ * pColset; } ;
struct TYPE_40__ {int /*<<< orphan*/  (* xNext ) (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_39__ {int nSegment; size_t nLevel; TYPE_3__* aLevel; } ;
struct TYPE_38__ {int nSeg; int /*<<< orphan*/ * aSeg; } ;
struct TYPE_37__ {size_t iFirst; } ;
typedef  int /*<<< orphan*/  Fts5StructureSegment ;
typedef  TYPE_3__ Fts5StructureLevel ;
typedef  TYPE_4__ Fts5Structure ;
typedef  TYPE_5__ Fts5SegIter ;
typedef  TYPE_6__ Fts5Iter ;
typedef  TYPE_7__ Fts5Index ;
typedef  int /*<<< orphan*/  Fts5Colset ;

/* Variables and functions */
 int FTS5INDEX_QUERY_DESC ; 
 int FTS5INDEX_QUERY_NOOUTPUT ; 
 int FTS5INDEX_QUERY_SKIPEMPTY ; 
 int MIN (int,int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5AssertMultiIterSetup (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fts5IterSetOutputCb (scalar_t__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fts5MultiIterAdvanced (TYPE_7__*,TYPE_6__*,int,int) ; 
 TYPE_6__* fts5MultiIterAlloc (TYPE_7__*,int) ; 
 int fts5MultiIterDoCompare (TYPE_6__*,int) ; 
 int /*<<< orphan*/  fts5MultiIterFree (TYPE_6__*) ; 
 scalar_t__ fts5MultiIterIsEmpty (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fts5MultiIterNext (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5MultiIterSetEof (TYPE_6__*) ; 
 int /*<<< orphan*/  fts5SegIterHashInit (TYPE_7__*,int /*<<< orphan*/  const*,int,int,TYPE_5__*) ; 
 int /*<<< orphan*/  fts5SegIterInit (TYPE_7__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  fts5SegIterSeekInit (TYPE_7__*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int fts5StructureCountSegments (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,TYPE_5__*) ; 

__attribute__((used)) static void fts5MultiIterNew(
  Fts5Index *p,                   /* FTS5 backend to iterate within */
  Fts5Structure *pStruct,         /* Structure of specific index */
  int flags,                      /* FTS5INDEX_QUERY_XXX flags */
  Fts5Colset *pColset,            /* Colset to filter on (or NULL) */
  const u8 *pTerm, int nTerm,     /* Term to seek to (or NULL/0) */
  int iLevel,                     /* Level to iterate (-1 for all) */
  int nSegment,                   /* Number of segments to merge (iLevel>=0) */
  Fts5Iter **ppOut                /* New object */
){
  int nSeg = 0;                   /* Number of segment-iters in use */
  int iIter = 0;                  /* */
  int iSeg;                       /* Used to iterate through segments */
  Fts5StructureLevel *pLvl;
  Fts5Iter *pNew;

  assert( (pTerm==0 && nTerm==0) || iLevel<0 );

  /* Allocate space for the new multi-seg-iterator. */
  if( p->rc==SQLITE_OK ){
    if( iLevel<0 ){
      assert( pStruct->nSegment==fts5StructureCountSegments(pStruct) );
      nSeg = pStruct->nSegment;
      nSeg += (p->pHash ? 1 : 0);
    }else{
      nSeg = MIN(pStruct->aLevel[iLevel].nSeg, nSegment);
    }
  }
  *ppOut = pNew = fts5MultiIterAlloc(p, nSeg);
  if( pNew==0 ) return;
  pNew->bRev = (0!=(flags & FTS5INDEX_QUERY_DESC));
  pNew->bSkipEmpty = (0!=(flags & FTS5INDEX_QUERY_SKIPEMPTY));
  pNew->pColset = pColset;
  if( (flags & FTS5INDEX_QUERY_NOOUTPUT)==0 ){
    fts5IterSetOutputCb(&p->rc, pNew);
  }

  /* Initialize each of the component segment iterators. */
  if( p->rc==SQLITE_OK ){
    if( iLevel<0 ){
      Fts5StructureLevel *pEnd = &pStruct->aLevel[pStruct->nLevel];
      if( p->pHash ){
        /* Add a segment iterator for the current contents of the hash table. */
        Fts5SegIter *pIter = &pNew->aSeg[iIter++];
        fts5SegIterHashInit(p, pTerm, nTerm, flags, pIter);
      }
      for(pLvl=&pStruct->aLevel[0]; pLvl<pEnd; pLvl++){
        for(iSeg=pLvl->nSeg-1; iSeg>=0; iSeg--){
          Fts5StructureSegment *pSeg = &pLvl->aSeg[iSeg];
          Fts5SegIter *pIter = &pNew->aSeg[iIter++];
          if( pTerm==0 ){
            fts5SegIterInit(p, pSeg, pIter);
          }else{
            fts5SegIterSeekInit(p, pTerm, nTerm, flags, pSeg, pIter);
          }
        }
      }
    }else{
      pLvl = &pStruct->aLevel[iLevel];
      for(iSeg=nSeg-1; iSeg>=0; iSeg--){
        fts5SegIterInit(p, &pLvl->aSeg[iSeg], &pNew->aSeg[iIter++]);
      }
    }
    assert( iIter==nSeg );
  }

  /* If the above was successful, each component iterators now points 
  ** to the first entry in its segment. In this case initialize the 
  ** aFirst[] array. Or, if an error has occurred, free the iterator
  ** object and set the output variable to NULL.  */
  if( p->rc==SQLITE_OK ){
    for(iIter=pNew->nSeg-1; iIter>0; iIter--){
      int iEq;
      if( (iEq = fts5MultiIterDoCompare(pNew, iIter)) ){
        Fts5SegIter *pSeg = &pNew->aSeg[iEq];
        if( p->rc==SQLITE_OK ) pSeg->xNext(p, pSeg, 0);
        fts5MultiIterAdvanced(p, pNew, iEq, iIter);
      }
    }
    fts5MultiIterSetEof(pNew);
    fts5AssertMultiIterSetup(p, pNew);

    if( pNew->bSkipEmpty && fts5MultiIterIsEmpty(p, pNew) ){
      fts5MultiIterNext(p, pNew, 0, 0);
    }else if( pNew->base.bEof==0 ){
      Fts5SegIter *pSeg = &pNew->aSeg[pNew->aFirst[1].iFirst];
      pNew->xSetOutputs(pNew, pSeg);
    }

  }else{
    fts5MultiIterFree(pNew);
    *ppOut = 0;
  }
}