#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ rc; } ;
struct TYPE_11__ {int nLevel; TYPE_1__* aLevel; } ;
struct TYPE_10__ {int nMerge; int nSeg; } ;
typedef  TYPE_1__ Fts5StructureLevel ;
typedef  TYPE_2__ Fts5Structure ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5IndexMergeLevel (TYPE_3__*,TYPE_2__**,int,int*) ; 
 int /*<<< orphan*/  fts5StructurePromote (TYPE_3__*,int,TYPE_2__*) ; 

__attribute__((used)) static int fts5IndexMerge(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5Structure **ppStruct,       /* IN/OUT: Current structure of index */
  int nPg,                        /* Pages of work to do */
  int nMin                        /* Minimum number of segments to merge */
){
  int nRem = nPg;
  int bRet = 0;
  Fts5Structure *pStruct = *ppStruct;
  while( nRem>0 && p->rc==SQLITE_OK ){
    int iLvl;                   /* To iterate through levels */
    int iBestLvl = 0;           /* Level offering the most input segments */
    int nBest = 0;              /* Number of input segments on best level */

    /* Set iBestLvl to the level to read input segments from. */
    assert( pStruct->nLevel>0 );
    for(iLvl=0; iLvl<pStruct->nLevel; iLvl++){
      Fts5StructureLevel *pLvl = &pStruct->aLevel[iLvl];
      if( pLvl->nMerge ){
        if( pLvl->nMerge>nBest ){
          iBestLvl = iLvl;
          nBest = pLvl->nMerge;
        }
        break;
      }
      if( pLvl->nSeg>nBest ){
        nBest = pLvl->nSeg;
        iBestLvl = iLvl;
      }
    }

    /* If nBest is still 0, then the index must be empty. */
#ifdef SQLITE_DEBUG
    for(iLvl=0; nBest==0 && iLvl<pStruct->nLevel; iLvl++){
      assert( pStruct->aLevel[iLvl].nSeg==0 );
    }
#endif

    if( nBest<nMin && pStruct->aLevel[iBestLvl].nMerge==0 ){
      break;
    }
    bRet = 1;
    fts5IndexMergeLevel(p, &pStruct, iBestLvl, &nRem);
    if( p->rc==SQLITE_OK && pStruct->aLevel[iBestLvl].nMerge==0 ){
      fts5StructurePromote(p, iBestLvl+1, pStruct);
    }
  }
  *ppStruct = pStruct;
  return bRet;
}