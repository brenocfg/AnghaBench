#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int /*<<< orphan*/  pDeleteRange; } ;
typedef  TYPE_1__ SqlDb ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sql_delete_range(
  TestDb *pTestDb, 
  void *pKey1, int nKey1,
  void *pKey2, int nKey2
){
  SqlDb *pDb = (SqlDb *)pTestDb;
  sqlite3_bind_blob(pDb->pDeleteRange, 1, pKey1, nKey1, SQLITE_STATIC);
  sqlite3_bind_blob(pDb->pDeleteRange, 2, pKey2, nKey2, SQLITE_STATIC);
  sqlite3_step(pDb->pDeleteRange);
  return sqlite3_reset(pDb->pDeleteRange);
}