#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int /*<<< orphan*/  db; int /*<<< orphan*/  pWriteRowid; } ;
typedef  TYPE_1__ Rtree ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtreeNewRowid(Rtree *pRtree, i64 *piRowid){
  int rc;
  sqlite3_bind_null(pRtree->pWriteRowid, 1);
  sqlite3_bind_null(pRtree->pWriteRowid, 2);
  sqlite3_step(pRtree->pWriteRowid);
  rc = sqlite3_reset(pRtree->pWriteRowid);
  *piRowid = sqlite3_last_insert_rowid(pRtree->db);
  return rc;
}