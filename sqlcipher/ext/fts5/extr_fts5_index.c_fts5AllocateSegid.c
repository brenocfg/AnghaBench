#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  aUsed ;
struct TYPE_11__ {scalar_t__ rc; } ;
struct TYPE_10__ {int nSegment; int nLevel; TYPE_2__* aLevel; } ;
struct TYPE_9__ {int nSeg; TYPE_1__* aSeg; } ;
struct TYPE_8__ {int iSegid; } ;
typedef  TYPE_3__ Fts5Structure ;
typedef  TYPE_4__ Fts5Index ;

/* Variables and functions */
 int FTS5_MAX_SEGMENT ; 
 scalar_t__ SQLITE_FULL ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert_nc (int) ; 
 int /*<<< orphan*/ * fts5IdxSelectStmt (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5AllocateSegid(Fts5Index *p, Fts5Structure *pStruct){
  int iSegid = 0;

  if( p->rc==SQLITE_OK ){
    if( pStruct->nSegment>=FTS5_MAX_SEGMENT ){
      p->rc = SQLITE_FULL;
    }else{
      /* FTS5_MAX_SEGMENT is currently defined as 2000. So the following
      ** array is 63 elements, or 252 bytes, in size.  */
      u32 aUsed[(FTS5_MAX_SEGMENT+31) / 32];
      int iLvl, iSeg;
      int i;
      u32 mask;
      memset(aUsed, 0, sizeof(aUsed));
      for(iLvl=0; iLvl<pStruct->nLevel; iLvl++){
        for(iSeg=0; iSeg<pStruct->aLevel[iLvl].nSeg; iSeg++){
          int iId = pStruct->aLevel[iLvl].aSeg[iSeg].iSegid;
          if( iId<=FTS5_MAX_SEGMENT && iId>0 ){
            aUsed[(iId-1) / 32] |= (u32)1 << ((iId-1) % 32);
          }
        }
      }

      for(i=0; aUsed[i]==0xFFFFFFFF; i++);
      mask = aUsed[i];
      for(iSegid=0; mask & ((u32)1 << iSegid); iSegid++);
      iSegid += 1 + i*32;

#ifdef SQLITE_DEBUG
      for(iLvl=0; iLvl<pStruct->nLevel; iLvl++){
        for(iSeg=0; iSeg<pStruct->aLevel[iLvl].nSeg; iSeg++){
          assert_nc( iSegid!=pStruct->aLevel[iLvl].aSeg[iSeg].iSegid );
        }
      }
      assert_nc( iSegid>0 && iSegid<=FTS5_MAX_SEGMENT );

      {
        sqlite3_stmt *pIdxSelect = fts5IdxSelectStmt(p);
        if( p->rc==SQLITE_OK ){
          u8 aBlob[2] = {0xff, 0xff};
          sqlite3_bind_int(pIdxSelect, 1, iSegid);
          sqlite3_bind_blob(pIdxSelect, 2, aBlob, 2, SQLITE_STATIC);
          assert_nc( sqlite3_step(pIdxSelect)!=SQLITE_ROW );
          p->rc = sqlite3_reset(pIdxSelect);
          sqlite3_bind_null(pIdxSelect, 2);
        }
      }
#endif
    }
  }

  return iSegid;
}