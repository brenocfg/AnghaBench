#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_8__ {scalar_t__ bTermEq; size_t iFirst; } ;
struct TYPE_7__ {scalar_t__ iSwitchRowid; int bRev; int nSeg; TYPE_3__* aFirst; TYPE_1__* aSeg; } ;
struct TYPE_6__ {scalar_t__ iRowid; int pLeaf; } ;
typedef  TYPE_1__ Fts5SegIter ;
typedef  TYPE_2__ Fts5Iter ;
typedef  TYPE_3__ Fts5CResult ;

/* Variables and functions */
 scalar_t__ LARGEST_INT64 ; 
 scalar_t__ SMALLEST_INT64 ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fts5MultiIterAdvanceRowid(
  Fts5Iter *pIter,                /* Iterator to update aFirst[] array for */
  int iChanged,                   /* Index of sub-iterator just advanced */
  Fts5SegIter **ppFirst
){
  Fts5SegIter *pNew = &pIter->aSeg[iChanged];

  if( pNew->iRowid==pIter->iSwitchRowid
   || (pNew->iRowid<pIter->iSwitchRowid)==pIter->bRev
  ){
    int i;
    Fts5SegIter *pOther = &pIter->aSeg[iChanged ^ 0x0001];
    pIter->iSwitchRowid = pIter->bRev ? SMALLEST_INT64 : LARGEST_INT64;
    for(i=(pIter->nSeg+iChanged)/2; 1; i=i/2){
      Fts5CResult *pRes = &pIter->aFirst[i];

      assert( pNew->pLeaf );
      assert( pRes->bTermEq==0 || pOther->pLeaf );

      if( pRes->bTermEq ){
        if( pNew->iRowid==pOther->iRowid ){
          return 1;
        }else if( (pOther->iRowid>pNew->iRowid)==pIter->bRev ){
          pIter->iSwitchRowid = pOther->iRowid;
          pNew = pOther;
        }else if( (pOther->iRowid>pIter->iSwitchRowid)==pIter->bRev ){
          pIter->iSwitchRowid = pOther->iRowid;
        }
      }
      pRes->iFirst = (u16)(pNew - pIter->aSeg);
      if( i==1 ) break;

      pOther = &pIter->aSeg[ pIter->aFirst[i ^ 0x0001].iFirst ];
    }
  }

  *ppFirst = pNew;
  return 0;
}