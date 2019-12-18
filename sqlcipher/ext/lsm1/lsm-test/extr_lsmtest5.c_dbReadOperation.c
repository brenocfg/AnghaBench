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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  TestDb ;
typedef  int /*<<< orphan*/  DbParameters ;

/* Variables and functions */
 int DB_KEY_BYTES ; 
 scalar_t__ dbComputeCksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  dbFormatCksumValue (scalar_t__,char*) ; 
 int /*<<< orphan*/  dbFormatKey (int /*<<< orphan*/ *,int,int,char*) ; 
 int dbMaxLevel (int /*<<< orphan*/ *) ; 
 scalar_t__ tdb_transaction_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testBegin (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  testCommit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testFetchStr (int /*<<< orphan*/ *,char*,char*,int*) ; 

__attribute__((used)) static void dbReadOperation(
  DbParameters *pParam,           /* Database parameters */
  TestDb *pDb,                    /* Database connection handle */
  void (*xDelay)(void *),
  void *pDelayCtx,
  int iKey,                       /* Key to read */
  int *pRc                        /* IN/OUT: Error code */
){
  const int iMax = dbMaxLevel(pParam);
  int i;

  if( tdb_transaction_support(pDb) ) testBegin(pDb, 1, pRc);
  for(i=1; *pRc==0 && i<=iMax; i++){
    char zCksum[DB_KEY_BYTES];
    char zKey[DB_KEY_BYTES];
    u32 iCksum = 0;

    iCksum = dbComputeCksum(pParam, pDb, i, iKey, pRc);
    if( iCksum ){
      if( xDelay && i==1 ) xDelay(pDelayCtx);
      dbFormatCksumValue(iCksum, zCksum);
      dbFormatKey(pParam, i, iKey, zKey);
      testFetchStr(pDb, zKey, zCksum, pRc);
    }
  }
  if( tdb_transaction_support(pDb) ) testCommit(pDb, 0, pRc);
}