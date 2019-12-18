#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_6__ {int nKey; } ;
typedef  TYPE_1__ DbParameters ;

/* Variables and functions */
 int DB_KEY_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbComputeCksum (TYPE_1__*,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  dbFormatCksumValue (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbFormatKey (TYPE_1__*,int,int,char*) ; 
 int dbMaxLevel (TYPE_1__*) ; 
 int tdb_begin (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tdb_transaction_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCommit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testWriteStr (int /*<<< orphan*/ *,char*,char const*,int*) ; 

__attribute__((used)) static int dbWriteOperation(
  DbParameters *pParam,           /* Database parameters */
  TestDb *pDb,                    /* Database connection handle */
  int iKey,                       /* Key to write to */
  const char *zValue,             /* Nul-terminated value to write */
  int *pRc                        /* IN/OUT: Error code */
){
  const int iMax = dbMaxLevel(pParam);
  char zKey[DB_KEY_BYTES];
  int i;
  int rc;

  assert( iKey>=0 && iKey<pParam->nKey );
  dbFormatKey(pParam, 0, iKey, zKey);

  /* Open a write transaction. This may fail - SQLITE4_BUSY */
  if( *pRc==0 && tdb_transaction_support(pDb) ){
    rc = tdb_begin(pDb, 2);
    if( rc==5 ) return 0;
    *pRc = rc;
  }

  testWriteStr(pDb, zKey, zValue, pRc);
  for(i=1; i<=iMax; i++){
    char zCksum[DB_KEY_BYTES];
    u32 iCksum = 0;

    iCksum = dbComputeCksum(pParam, pDb, i, iKey, pRc);
    dbFormatCksumValue(iCksum, zCksum);
    dbFormatKey(pParam, i, iKey, zKey);
    testWriteStr(pDb, zKey, zCksum, pRc);
  }
  if( tdb_transaction_support(pDb) ) testCommit(pDb, 0, pRc);
  return 1;
}