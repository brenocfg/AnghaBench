#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nLevel; TYPE_2__* aLevel; } ;
struct TYPE_6__ {int nSeg; TYPE_1__* aSeg; int /*<<< orphan*/  nMerge; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgnoLast; int /*<<< orphan*/  pgnoFirst; int /*<<< orphan*/  iSegid; } ;
typedef  TYPE_1__ Fts5StructureSegment ;
typedef  TYPE_2__ Fts5StructureLevel ;
typedef  TYPE_3__ Fts5Structure ;
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts5BufferAppendPrintf (int*,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void fts5DebugStructure(
  int *pRc,                       /* IN/OUT: error code */
  Fts5Buffer *pBuf,
  Fts5Structure *p
){
  int iLvl, iSeg;                 /* Iterate through levels, segments */

  for(iLvl=0; iLvl<p->nLevel; iLvl++){
    Fts5StructureLevel *pLvl = &p->aLevel[iLvl];
    sqlite3Fts5BufferAppendPrintf(pRc, pBuf, 
        " {lvl=%d nMerge=%d nSeg=%d", iLvl, pLvl->nMerge, pLvl->nSeg
    );
    for(iSeg=0; iSeg<pLvl->nSeg; iSeg++){
      Fts5StructureSegment *pSeg = &pLvl->aSeg[iSeg];
      sqlite3Fts5BufferAppendPrintf(pRc, pBuf, " {id=%d leaves=%d..%d}", 
          pSeg->iSegid, pSeg->pgnoFirst, pSeg->pgnoLast
      );
    }
    sqlite3Fts5BufferAppendPrintf(pRc, pBuf, "}");
  }
}