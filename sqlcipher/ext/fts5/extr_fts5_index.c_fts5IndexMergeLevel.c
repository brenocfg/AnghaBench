#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_55__   TYPE_9__ ;
typedef  struct TYPE_54__   TYPE_8__ ;
typedef  struct TYPE_53__   TYPE_7__ ;
typedef  struct TYPE_52__   TYPE_6__ ;
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_2__ ;
typedef  struct TYPE_47__   TYPE_1__ ;
typedef  struct TYPE_46__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_55__ {TYPE_3__* aFirst; TYPE_8__* aSeg; } ;
struct TYPE_54__ {int nPos; int bDel; } ;
struct TYPE_48__ {scalar_t__ pgno; int /*<<< orphan*/  buf; } ;
struct TYPE_53__ {int n; int nLeafWritten; TYPE_2__ writer; int /*<<< orphan*/  p; scalar_t__ iBtPage; } ;
struct TYPE_52__ {int nLevel; scalar_t__ nSegment; TYPE_5__* aLevel; } ;
struct TYPE_51__ {int nMerge; int nSeg; TYPE_4__* aSeg; } ;
struct TYPE_50__ {int iSegid; scalar_t__ pgnoLast; int pgnoFirst; } ;
struct TYPE_49__ {size_t iFirst; } ;
struct TYPE_47__ {int eDetail; } ;
struct TYPE_46__ {scalar_t__ rc; TYPE_1__* pConfig; } ;
typedef  TYPE_4__ Fts5StructureSegment ;
typedef  TYPE_5__ Fts5StructureLevel ;
typedef  TYPE_6__ Fts5Structure ;
typedef  TYPE_7__ Fts5SegWriter ;
typedef  TYPE_8__ Fts5SegIter ;
typedef  TYPE_9__ Fts5Iter ;
typedef  TYPE_10__ Fts5Index ;
typedef  TYPE_7__ Fts5Buffer ;

/* Variables and functions */
 int FTS5INDEX_QUERY_NOOUTPUT ; 
 int FTS5_DETAIL_NONE ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5AllocateSegid (TYPE_10__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fts5BufferAppendVarint (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5BufferFree (TYPE_7__*) ; 
 int /*<<< orphan*/  fts5BufferSet (scalar_t__*,TYPE_7__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5ChunkIterate (TYPE_10__*,TYPE_8__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5DataRemoveSegment (TYPE_10__*,int) ; 
 scalar_t__ fts5Memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fts5MergeChunkCallback ; 
 scalar_t__ fts5MultiIterEof (TYPE_10__*,TYPE_9__*) ; 
 int /*<<< orphan*/  fts5MultiIterFree (TYPE_9__*) ; 
 int /*<<< orphan*/  fts5MultiIterNew (TYPE_10__*,TYPE_6__*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_9__**) ; 
 int /*<<< orphan*/  fts5MultiIterNext (TYPE_10__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5MultiIterRowid (TYPE_9__*) ; 
 int /*<<< orphan*/ * fts5MultiIterTerm (TYPE_9__*,int*) ; 
 int /*<<< orphan*/  fts5StructureAddLevel (scalar_t__*,TYPE_6__**) ; 
 int /*<<< orphan*/  fts5StructureExtendLevel (scalar_t__*,TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5TrimSegments (TYPE_10__*,TYPE_9__*) ; 
 int /*<<< orphan*/  fts5WriteAppendRowid (TYPE_10__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5WriteAppendTerm (TYPE_10__*,TYPE_7__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5WriteFinish (TYPE_10__*,TYPE_7__*,scalar_t__*) ; 
 int /*<<< orphan*/  fts5WriteInit (TYPE_10__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fts5IndexMergeLevel(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5Structure **ppStruct,       /* IN/OUT: Stucture of index */
  int iLvl,                       /* Level to read input from */
  int *pnRem                      /* Write up to this many output leaves */
){
  Fts5Structure *pStruct = *ppStruct;
  Fts5StructureLevel *pLvl = &pStruct->aLevel[iLvl];
  Fts5StructureLevel *pLvlOut;
  Fts5Iter *pIter = 0;       /* Iterator to read input data */
  int nRem = pnRem ? *pnRem : 0;  /* Output leaf pages left to write */
  int nInput;                     /* Number of input segments */
  Fts5SegWriter writer;           /* Writer object */
  Fts5StructureSegment *pSeg;     /* Output segment */
  Fts5Buffer term;
  int bOldest;                    /* True if the output segment is the oldest */
  int eDetail = p->pConfig->eDetail;
  const int flags = FTS5INDEX_QUERY_NOOUTPUT;
  int bTermWritten = 0;           /* True if current term already output */

  assert( iLvl<pStruct->nLevel );
  assert( pLvl->nMerge<=pLvl->nSeg );

  memset(&writer, 0, sizeof(Fts5SegWriter));
  memset(&term, 0, sizeof(Fts5Buffer));
  if( pLvl->nMerge ){
    pLvlOut = &pStruct->aLevel[iLvl+1];
    assert( pLvlOut->nSeg>0 );
    nInput = pLvl->nMerge;
    pSeg = &pLvlOut->aSeg[pLvlOut->nSeg-1];

    fts5WriteInit(p, &writer, pSeg->iSegid);
    writer.writer.pgno = pSeg->pgnoLast+1;
    writer.iBtPage = 0;
  }else{
    int iSegid = fts5AllocateSegid(p, pStruct);

    /* Extend the Fts5Structure object as required to ensure the output
    ** segment exists. */
    if( iLvl==pStruct->nLevel-1 ){
      fts5StructureAddLevel(&p->rc, ppStruct);
      pStruct = *ppStruct;
    }
    fts5StructureExtendLevel(&p->rc, pStruct, iLvl+1, 1, 0);
    if( p->rc ) return;
    pLvl = &pStruct->aLevel[iLvl];
    pLvlOut = &pStruct->aLevel[iLvl+1];

    fts5WriteInit(p, &writer, iSegid);

    /* Add the new segment to the output level */
    pSeg = &pLvlOut->aSeg[pLvlOut->nSeg];
    pLvlOut->nSeg++;
    pSeg->pgnoFirst = 1;
    pSeg->iSegid = iSegid;
    pStruct->nSegment++;

    /* Read input from all segments in the input level */
    nInput = pLvl->nSeg;
  }
  bOldest = (pLvlOut->nSeg==1 && pStruct->nLevel==iLvl+2);

  assert( iLvl>=0 );
  for(fts5MultiIterNew(p, pStruct, flags, 0, 0, 0, iLvl, nInput, &pIter);
      fts5MultiIterEof(p, pIter)==0;
      fts5MultiIterNext(p, pIter, 0, 0)
  ){
    Fts5SegIter *pSegIter = &pIter->aSeg[ pIter->aFirst[1].iFirst ];
    int nPos;                     /* position-list size field value */
    int nTerm;
    const u8 *pTerm;

    pTerm = fts5MultiIterTerm(pIter, &nTerm);
    if( nTerm!=term.n || fts5Memcmp(pTerm, term.p, nTerm) ){
      if( pnRem && writer.nLeafWritten>nRem ){
        break;
      }
      fts5BufferSet(&p->rc, &term, nTerm, pTerm);
      bTermWritten =0;
    }

    /* Check for key annihilation. */
    if( pSegIter->nPos==0 && (bOldest || pSegIter->bDel==0) ) continue;

    if( p->rc==SQLITE_OK && bTermWritten==0 ){
      /* This is a new term. Append a term to the output segment. */
      fts5WriteAppendTerm(p, &writer, nTerm, pTerm);
      bTermWritten = 1;
    }

    /* Append the rowid to the output */
    /* WRITEPOSLISTSIZE */
    fts5WriteAppendRowid(p, &writer, fts5MultiIterRowid(pIter));

    if( eDetail==FTS5_DETAIL_NONE ){
      if( pSegIter->bDel ){
        fts5BufferAppendVarint(&p->rc, &writer.writer.buf, 0);
        if( pSegIter->nPos>0 ){
          fts5BufferAppendVarint(&p->rc, &writer.writer.buf, 0);
        }
      }
    }else{
      /* Append the position-list data to the output */
      nPos = pSegIter->nPos*2 + pSegIter->bDel;
      fts5BufferAppendVarint(&p->rc, &writer.writer.buf, nPos);
      fts5ChunkIterate(p, pSegIter, (void*)&writer, fts5MergeChunkCallback);
    }
  }

  /* Flush the last leaf page to disk. Set the output segment b-tree height
  ** and last leaf page number at the same time.  */
  fts5WriteFinish(p, &writer, &pSeg->pgnoLast);

  if( fts5MultiIterEof(p, pIter) ){
    int i;

    /* Remove the redundant segments from the %_data table */
    for(i=0; i<nInput; i++){
      fts5DataRemoveSegment(p, pLvl->aSeg[i].iSegid);
    }

    /* Remove the redundant segments from the input level */
    if( pLvl->nSeg!=nInput ){
      int nMove = (pLvl->nSeg - nInput) * sizeof(Fts5StructureSegment);
      memmove(pLvl->aSeg, &pLvl->aSeg[nInput], nMove);
    }
    pStruct->nSegment -= nInput;
    pLvl->nSeg -= nInput;
    pLvl->nMerge = 0;
    if( pSeg->pgnoLast==0 ){
      pLvlOut->nSeg--;
      pStruct->nSegment--;
    }
  }else{
    assert( pSeg->pgnoLast>0 );
    fts5TrimSegments(p, pIter);
    pLvl->nMerge = nInput;
  }

  fts5MultiIterFree(pIter);
  fts5BufferFree(&term);
  if( pnRem ) *pnRem -= writer.nLeafWritten;
}