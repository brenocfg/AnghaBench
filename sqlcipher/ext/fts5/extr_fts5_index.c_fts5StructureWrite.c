#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_21__ {int n; int /*<<< orphan*/  p; } ;
struct TYPE_20__ {scalar_t__ rc; TYPE_1__* pConfig; } ;
struct TYPE_19__ {int nSegment; int nLevel; TYPE_3__* aLevel; scalar_t__ nWriteCounter; } ;
struct TYPE_18__ {int nMerge; int nSeg; TYPE_2__* aSeg; } ;
struct TYPE_17__ {int iSegid; int pgnoFirst; int pgnoLast; } ;
struct TYPE_16__ {int iCookie; } ;
typedef  TYPE_3__ Fts5StructureLevel ;
typedef  TYPE_4__ Fts5Structure ;
typedef  TYPE_5__ Fts5Index ;
typedef  TYPE_6__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_STRUCTURE_ROWID ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5BufferAppendVarint (scalar_t__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  fts5BufferFree (TYPE_6__*) ; 
 int /*<<< orphan*/  fts5BufferSafeAppendVarint (TYPE_6__*,int) ; 
 int /*<<< orphan*/  fts5DataWrite (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int fts5StructureCountSegments (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts5BufferSize (scalar_t__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5Put32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fts5StructureWrite(Fts5Index *p, Fts5Structure *pStruct){
  if( p->rc==SQLITE_OK ){
    Fts5Buffer buf;               /* Buffer to serialize record into */
    int iLvl;                     /* Used to iterate through levels */
    int iCookie;                  /* Cookie value to store */

    assert( pStruct->nSegment==fts5StructureCountSegments(pStruct) );
    memset(&buf, 0, sizeof(Fts5Buffer));

    /* Append the current configuration cookie */
    iCookie = p->pConfig->iCookie;
    if( iCookie<0 ) iCookie = 0;

    if( 0==sqlite3Fts5BufferSize(&p->rc, &buf, 4+9+9+9) ){
      sqlite3Fts5Put32(buf.p, iCookie);
      buf.n = 4;
      fts5BufferSafeAppendVarint(&buf, pStruct->nLevel);
      fts5BufferSafeAppendVarint(&buf, pStruct->nSegment);
      fts5BufferSafeAppendVarint(&buf, (i64)pStruct->nWriteCounter);
    }

    for(iLvl=0; iLvl<pStruct->nLevel; iLvl++){
      int iSeg;                     /* Used to iterate through segments */
      Fts5StructureLevel *pLvl = &pStruct->aLevel[iLvl];
      fts5BufferAppendVarint(&p->rc, &buf, pLvl->nMerge);
      fts5BufferAppendVarint(&p->rc, &buf, pLvl->nSeg);
      assert( pLvl->nMerge<=pLvl->nSeg );

      for(iSeg=0; iSeg<pLvl->nSeg; iSeg++){
        fts5BufferAppendVarint(&p->rc, &buf, pLvl->aSeg[iSeg].iSegid);
        fts5BufferAppendVarint(&p->rc, &buf, pLvl->aSeg[iSeg].pgnoFirst);
        fts5BufferAppendVarint(&p->rc, &buf, pLvl->aSeg[iSeg].pgnoLast);
      }
    }

    fts5DataWrite(p, FTS5_STRUCTURE_ROWID, buf.p, buf.n);
    fts5BufferFree(&buf);
  }
}