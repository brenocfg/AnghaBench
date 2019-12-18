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

/* Variables and functions */
 int /*<<< orphan*/  LSMTEST6_TESTDB ; 
 int LSM_OK ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testDeleteLsmdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testOomOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  testOomWriteStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int*) ; 

__attribute__((used)) static void simple_oom_4(OomTest *pOom){
  int rc = LSM_OK;
  lsm_db *pDb;

  testDeleteLsmdb(LSMTEST6_TESTDB);
  testOomOpen(pOom, LSMTEST6_TESTDB, &pDb, &rc);

  testOomWriteStr(pOom, pDb, "123", "onetwothree", &rc);
  testOomWriteStr(pOom, pDb, "456", "fourfivesix", &rc);
  testOomWriteStr(pOom, pDb, "789", "seveneightnine", &rc);
  testOomWriteStr(pOom, pDb, "123", "teneleventwelve", &rc);
  testOomWriteStr(pOom, pDb, "456", "fourteenfifteensixteen", &rc);

  lsm_close(pDb);
}