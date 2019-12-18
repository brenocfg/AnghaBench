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
struct TYPE_2__ {int nOpenTrans; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ SqlDb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int) ; 

__attribute__((used)) static int sql_commit(TestDb *pTestDb, int iLevel){
  SqlDb *pDb = (SqlDb *)pTestDb;
  assert( iLevel>=0 );

  /* Close the read transaction if requested. */
  if( pDb->nOpenTrans>=1 && iLevel==0 ){
    int rc = sqlite3_exec(pDb->db, "COMMIT", 0, 0, 0);
    if( rc!=0 ) return rc;
    pDb->nOpenTrans = 0;
  }

  /* Close write transactions as required */
  if( pDb->nOpenTrans>iLevel ){
    char *zSql = sqlite3_mprintf("RELEASE x%d", iLevel);
    int rc = sqlite3_exec(pDb->db, zSql, 0, 0, 0);
    sqlite3_free(zSql);
    if( rc!=0 ) return rc;
  }

  pDb->nOpenTrans = iLevel;
  return 0;
}