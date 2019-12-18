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
struct TYPE_2__ {scalar_t__ aAlloc; int /*<<< orphan*/  db; int /*<<< orphan*/ * apScan; int /*<<< orphan*/  pFetch; int /*<<< orphan*/  pDeleteRange; int /*<<< orphan*/  pDelete; int /*<<< orphan*/  pInsert; } ;
typedef  TYPE_1__ SqlDb ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sql_close(TestDb *pTestDb){
  SqlDb *pDb = (SqlDb *)pTestDb;
  sqlite3_finalize(pDb->pInsert);
  sqlite3_finalize(pDb->pDelete);
  sqlite3_finalize(pDb->pDeleteRange);
  sqlite3_finalize(pDb->pFetch);
  sqlite3_finalize(pDb->apScan[0]);
  sqlite3_finalize(pDb->apScan[1]);
  sqlite3_finalize(pDb->apScan[2]);
  sqlite3_finalize(pDb->apScan[3]);
  sqlite3_finalize(pDb->apScan[4]);
  sqlite3_finalize(pDb->apScan[5]);
  sqlite3_finalize(pDb->apScan[6]);
  sqlite3_finalize(pDb->apScan[7]);
  sqlite3_close(pDb->db);
  free((char *)pDb->aAlloc);
  free((char *)pDb);
  return SQLITE_OK;
}