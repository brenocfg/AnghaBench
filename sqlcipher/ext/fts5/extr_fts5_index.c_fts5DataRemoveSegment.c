#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_7__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; } ;
struct TYPE_6__ {scalar_t__ pIdxDeleter; scalar_t__ rc; TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_SEGMENT_ROWID (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  fts5DataDelete (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fts5IndexPrepareStmt (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (scalar_t__,int,int) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_reset (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_step (scalar_t__) ; 

__attribute__((used)) static void fts5DataRemoveSegment(Fts5Index *p, int iSegid){
  i64 iFirst = FTS5_SEGMENT_ROWID(iSegid, 0);
  i64 iLast = FTS5_SEGMENT_ROWID(iSegid+1, 0)-1;
  fts5DataDelete(p, iFirst, iLast);
  if( p->pIdxDeleter==0 ){
    Fts5Config *pConfig = p->pConfig;
    fts5IndexPrepareStmt(p, &p->pIdxDeleter, sqlite3_mprintf(
          "DELETE FROM '%q'.'%q_idx' WHERE segid=?",
          pConfig->zDb, pConfig->zName
    ));
  }
  if( p->rc==SQLITE_OK ){
    sqlite3_bind_int(p->pIdxDeleter, 1, iSegid);
    sqlite3_step(p->pIdxDeleter);
    p->rc = sqlite3_reset(p->pIdxDeleter);
  }
}