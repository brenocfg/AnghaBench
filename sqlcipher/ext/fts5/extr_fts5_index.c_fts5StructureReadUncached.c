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
struct TYPE_11__ {int iCookie; } ;
struct TYPE_10__ {size_t nn; int /*<<< orphan*/ * p; } ;
struct TYPE_9__ {int /*<<< orphan*/  rc; TYPE_3__* pConfig; } ;
typedef  int /*<<< orphan*/  Fts5Structure ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5Data ;
typedef  TYPE_3__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_DATA_PADDING ; 
 int /*<<< orphan*/  FTS5_STRUCTURE_ROWID ; 
 int /*<<< orphan*/  SQLITE_OK ; 
 TYPE_2__* fts5DataRead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  fts5StructureDecode (int /*<<< orphan*/ *,size_t,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fts5StructureRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts5ConfigLoad (TYPE_3__*,int) ; 

__attribute__((used)) static Fts5Structure *fts5StructureReadUncached(Fts5Index *p){
  Fts5Structure *pRet = 0;
  Fts5Config *pConfig = p->pConfig;
  int iCookie;                    /* Configuration cookie */
  Fts5Data *pData;

  pData = fts5DataRead(p, FTS5_STRUCTURE_ROWID);
  if( p->rc==SQLITE_OK ){
    /* TODO: Do we need this if the leaf-index is appended? Probably... */
    memset(&pData->p[pData->nn], 0, FTS5_DATA_PADDING);
    p->rc = fts5StructureDecode(pData->p, pData->nn, &iCookie, &pRet);
    if( p->rc==SQLITE_OK && pConfig->iCookie!=iCookie ){
      p->rc = sqlite3Fts5ConfigLoad(pConfig, iCookie);
    }
    fts5DataRelease(pData);
    if( p->rc!=SQLITE_OK ){
      fts5StructureRelease(pRet);
      pRet = 0;
    }
  }

  return pRet;
}