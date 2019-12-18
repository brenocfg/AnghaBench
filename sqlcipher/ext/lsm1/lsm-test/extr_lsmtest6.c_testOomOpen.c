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
 int LSM_OK ; 
 int lsm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_open (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tdb_lsm_env () ; 
 int /*<<< orphan*/  testOomAssertRc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void testOomOpen(
  OomTest *pOom,
  const char *zName,
  lsm_db **ppDb,
  int *pRc
){
  if( *pRc==LSM_OK ){
    int rc;
    rc = lsm_new(tdb_lsm_env(), ppDb);
    if( rc==LSM_OK ) rc = lsm_open(*ppDb, zName);
    testOomAssertRc(pOom, rc);
    *pRc = rc;
  }
}