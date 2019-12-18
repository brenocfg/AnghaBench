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

/* Variables and functions */
 int ArraySize (char const**) ; 
 int /*<<< orphan*/  LSMTEST6_TESTDB ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmWriteStr (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ *) ; 
 int lsm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdb_lsm_env () ; 
 int /*<<< orphan*/  testDeleteLsmdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testSaveDb (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void setup_populate_db(void){
  const char *azStr[] = {
    "one",   "one",
    "two",   "four",
    "three", "nine",
    "four",  "sixteen",
    "five",  "twentyfive",
    "six",   "thirtysix",
    "seven", "fourtynine",
    "eight", "sixtyfour",
  };
  int rc;
  int ii;
  lsm_db *pDb;

  testDeleteLsmdb(LSMTEST6_TESTDB);

  rc = lsm_new(tdb_lsm_env(), &pDb);
  if( rc==LSM_OK ) rc = lsm_open(pDb, LSMTEST6_TESTDB);

  for(ii=0; rc==LSM_OK && ii<ArraySize(azStr); ii+=2){
    rc = lsmWriteStr(pDb, azStr[ii], azStr[ii+1]);
  }
  lsm_close(pDb);

  testSaveDb(LSMTEST6_TESTDB, "log");
  assert( rc==LSM_OK );
}