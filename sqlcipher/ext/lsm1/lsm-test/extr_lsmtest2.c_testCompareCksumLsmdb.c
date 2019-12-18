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
typedef  int /*<<< orphan*/  TestDb ;

/* Variables and functions */
 int TEST_CKSUM_BYTES ; 
 int strcmp (char*,char const*) ; 
 int tdb_lsm_open (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCksumDatabase (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testPrintError (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  test_failed () ; 

__attribute__((used)) static void testCompareCksumLsmdb(
  const char *zFile,              /* Path to LSM database */
  int bCompress,                  /* True if db is compressed */
  const char *zExpect1,           /* Expected checksum 1 */
  const char *zExpect2,           /* Expected checksum 2 (or NULL) */
  int *pRc                        /* IN/OUT: Test case error code */
){
  if( *pRc==0 ){
    char zCksum[TEST_CKSUM_BYTES];
    TestDb *pDb;

    *pRc = tdb_lsm_open((bCompress?"compression=1 mmap=0":""), zFile, 0, &pDb);
    testCksumDatabase(pDb, zCksum);
    testClose(&pDb);

    if( *pRc==0 ){
      int r1 = 0;
      int r2 = -1;

      r1 = strcmp(zCksum, zExpect1);
      if( zExpect2 ) r2 = strcmp(zCksum, zExpect2);
      if( r1 && r2 ){
        if( zExpect2 ){
          testPrintError("testCompareCksumLsmdb: \"%s\" != (\"%s\" OR \"%s\")",
              zCksum, zExpect1, zExpect2
          );
        }else{
          testPrintError("testCompareCksumLsmdb: \"%s\" != \"%s\"",
              zCksum, zExpect1
          );
        }
        *pRc = 1;
        test_failed();
      }
    }
  }
}