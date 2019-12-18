#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  OomTest ;
typedef  int /*<<< orphan*/  Datasource ;

/* Variables and functions */
 int /*<<< orphan*/  LSMTEST6_TESTDB ; 
 int LSM_OK ; 
 int /*<<< orphan*/ * getDatasource () ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDatasourceFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testOomFetchData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testOomOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testRestoreDb (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void simple_oom_5(OomTest *pOom){
  Datasource *pData = getDatasource();
  int rc = LSM_OK;
  lsm_db *pDb;

  testRestoreDb(LSMTEST6_TESTDB, "log");
  testOomOpen(pOom, LSMTEST6_TESTDB, &pDb, &rc);

  testOomFetchData(pOom, pDb, pData, 3333, &rc);
  testOomFetchData(pOom, pDb, pData, 0, &rc);
  testOomFetchData(pOom, pDb, pData, 4999, &rc);

  lsm_close(pDb);
  testDatasourceFree(pData);
}