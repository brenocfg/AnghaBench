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

/* Type definitions */
struct TYPE_20__ {scalar_t__ rc; } ;
struct TYPE_19__ {scalar_t__ nSegment; TYPE_1__* aLevel; } ;
struct TYPE_18__ {scalar_t__ nSeg; } ;
typedef  TYPE_2__ Fts5Structure ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 int FTS5_OPT_WORK_UNIT ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5IndexFlush (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5IndexMergeLevel (TYPE_3__*,TYPE_2__**,int,int*) ; 
 TYPE_2__* fts5IndexOptimizeStruct (TYPE_3__*,TYPE_2__*) ; 
 int fts5IndexReturn (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5StructureInvalidate (TYPE_3__*) ; 
 TYPE_2__* fts5StructureRead (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5StructureRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  fts5StructureWrite (TYPE_3__*,TYPE_2__*) ; 

int sqlite3Fts5IndexOptimize(Fts5Index *p){
  Fts5Structure *pStruct;
  Fts5Structure *pNew = 0;

  assert( p->rc==SQLITE_OK );
  fts5IndexFlush(p);
  pStruct = fts5StructureRead(p);
  fts5StructureInvalidate(p);

  if( pStruct ){
    pNew = fts5IndexOptimizeStruct(p, pStruct);
  }
  fts5StructureRelease(pStruct);

  assert( pNew==0 || pNew->nSegment>0 );
  if( pNew ){
    int iLvl;
    for(iLvl=0; pNew->aLevel[iLvl].nSeg==0; iLvl++){}
    while( p->rc==SQLITE_OK && pNew->aLevel[iLvl].nSeg>0 ){
      int nRem = FTS5_OPT_WORK_UNIT;
      fts5IndexMergeLevel(p, &pNew, iLvl, &nRem);
    }

    fts5StructureWrite(p, pNew);
    fts5StructureRelease(pNew);
  }

  return fts5IndexReturn(p); 
}