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

/* Variables and functions */
 int /*<<< orphan*/  do_crash_test (char const*,int*) ; 
 int /*<<< orphan*/  do_writer_crash_test (char const*,int*) ; 
 scalar_t__ tdb_system_name (int) ; 
 int /*<<< orphan*/  testPrintError (char*) ; 
 int /*<<< orphan*/  test_api (char const*,int*) ; 
 int /*<<< orphan*/  test_data_1 (scalar_t__,char const*,int*) ; 
 int /*<<< orphan*/  test_data_2 (scalar_t__,char const*,int*) ; 
 int /*<<< orphan*/  test_data_3 (scalar_t__,char const*,int*) ; 
 int /*<<< orphan*/  test_data_4 (scalar_t__,char const*,int*) ; 
 int /*<<< orphan*/  test_mc (scalar_t__,char const*,int*) ; 
 int /*<<< orphan*/  test_mt (scalar_t__,char const*,int*) ; 
 int /*<<< orphan*/  test_oom (char const*,int*) ; 
 int /*<<< orphan*/  test_rollback (scalar_t__,char const*,int*) ; 

int do_test(int nArg, char **azArg){
  int j;
  int rc;
  int nFail = 0;
  const char *zPattern = 0;

  if( nArg>1 ){
    testPrintError("Usage: test ?PATTERN?\n");
    return 1;
  }
  if( nArg==1 ){
    zPattern = azArg[0];
  }

  for(j=0; tdb_system_name(j); j++){
    rc = 0;

    test_data_1(tdb_system_name(j), zPattern, &rc);
    test_data_2(tdb_system_name(j), zPattern, &rc);
    test_data_3(tdb_system_name(j), zPattern, &rc);
    test_data_4(tdb_system_name(j), zPattern, &rc);
    test_rollback(tdb_system_name(j), zPattern, &rc);
    test_mc(tdb_system_name(j), zPattern, &rc);
    test_mt(tdb_system_name(j), zPattern, &rc);

    if( rc ) nFail++;
  }

  rc = 0;
  test_oom(zPattern, &rc);
  if( rc ) nFail++;

  rc = 0;
  test_api(zPattern, &rc);
  if( rc ) nFail++;

  rc = 0;
  do_crash_test(zPattern, &rc);
  if( rc ) nFail++;

  rc = 0;
  do_writer_crash_test(zPattern, &rc);
  if( rc ) nFail++;

  return (nFail!=0);
}