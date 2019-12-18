#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nLvl; int /*<<< orphan*/  iSegid; TYPE_2__* aLvl; } ;
struct TYPE_10__ {int /*<<< orphan*/  iLeafPgno; int /*<<< orphan*/  pData; scalar_t__ bEof; } ;
struct TYPE_9__ {scalar_t__ rc; } ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5DlidxLvl ;
typedef  TYPE_3__ Fts5DlidxIter ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_DLIDX_ROWID (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  fts5DataRead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5DataRelease (int /*<<< orphan*/ ) ; 
 scalar_t__ fts5DlidxLvlNext (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fts5DlidxIterLast(Fts5Index *p, Fts5DlidxIter *pIter){
  int i;

  /* Advance each level to the last entry on the last page */
  for(i=pIter->nLvl-1; p->rc==SQLITE_OK && i>=0; i--){
    Fts5DlidxLvl *pLvl = &pIter->aLvl[i];
    while( fts5DlidxLvlNext(pLvl)==0 );
    pLvl->bEof = 0;

    if( i>0 ){
      Fts5DlidxLvl *pChild = &pLvl[-1];
      fts5DataRelease(pChild->pData);
      memset(pChild, 0, sizeof(Fts5DlidxLvl));
      pChild->pData = fts5DataRead(p, 
          FTS5_DLIDX_ROWID(pIter->iSegid, i-1, pLvl->iLeafPgno)
      );
    }
  }
}