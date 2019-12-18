#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {TYPE_1__* pConfig; int /*<<< orphan*/  pIndex; scalar_t__ bTotalsValid; } ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Fts5Storage ;

/* Variables and functions */
 int SQLITE_OK ; 
 int fts5StorageSaveTotals (TYPE_2__*) ; 
 int sqlite3Fts5IndexSync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_set_last_insert_rowid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3Fts5StorageSync(Fts5Storage *p){
  int rc = SQLITE_OK;
  i64 iLastRowid = sqlite3_last_insert_rowid(p->pConfig->db);
  if( p->bTotalsValid ){
    rc = fts5StorageSaveTotals(p);
    p->bTotalsValid = 0;
  }
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts5IndexSync(p->pIndex);
  }
  sqlite3_set_last_insert_rowid(p->pConfig->db, iLastRowid);
  return rc;
}