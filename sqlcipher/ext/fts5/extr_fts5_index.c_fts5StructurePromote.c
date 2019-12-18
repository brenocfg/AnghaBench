#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ rc; } ;
struct TYPE_11__ {TYPE_2__* aLevel; } ;
struct TYPE_10__ {int nSeg; scalar_t__ nMerge; TYPE_1__* aSeg; } ;
struct TYPE_9__ {int pgnoLast; int pgnoFirst; } ;
typedef  TYPE_1__ Fts5StructureSegment ;
typedef  TYPE_2__ Fts5StructureLevel ;
typedef  TYPE_3__ Fts5Structure ;
typedef  TYPE_4__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5StructurePromoteTo (TYPE_4__*,int,int,TYPE_3__*) ; 

__attribute__((used)) static void fts5StructurePromote(
  Fts5Index *p,                   /* FTS5 backend object */
  int iLvl,                       /* Index level just updated */
  Fts5Structure *pStruct          /* Index structure */
){
  if( p->rc==SQLITE_OK ){
    int iTst;
    int iPromote = -1;
    int szPromote = 0;            /* Promote anything this size or smaller */
    Fts5StructureSegment *pSeg;   /* Segment just written */
    int szSeg;                    /* Size of segment just written */
    int nSeg = pStruct->aLevel[iLvl].nSeg;

    if( nSeg==0 ) return;
    pSeg = &pStruct->aLevel[iLvl].aSeg[pStruct->aLevel[iLvl].nSeg-1];
    szSeg = (1 + pSeg->pgnoLast - pSeg->pgnoFirst);

    /* Check for condition (a) */
    for(iTst=iLvl-1; iTst>=0 && pStruct->aLevel[iTst].nSeg==0; iTst--);
    if( iTst>=0 ){
      int i;
      int szMax = 0;
      Fts5StructureLevel *pTst = &pStruct->aLevel[iTst];
      assert( pTst->nMerge==0 );
      for(i=0; i<pTst->nSeg; i++){
        int sz = pTst->aSeg[i].pgnoLast - pTst->aSeg[i].pgnoFirst + 1;
        if( sz>szMax ) szMax = sz;
      }
      if( szMax>=szSeg ){
        /* Condition (a) is true. Promote the newest segment on level 
        ** iLvl to level iTst.  */
        iPromote = iTst;
        szPromote = szMax;
      }
    }

    /* If condition (a) is not met, assume (b) is true. StructurePromoteTo()
    ** is a no-op if it is not.  */
    if( iPromote<0 ){
      iPromote = iLvl;
      szPromote = szSeg;
    }
    fts5StructurePromoteTo(p, iPromote, szPromote, pStruct);
  }
}