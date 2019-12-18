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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int nAlloc; int /*<<< orphan*/  pFetch; int /*<<< orphan*/ * aAlloc; } ;
typedef  TYPE_1__ SqlDb ;

/* Variables and functions */
 int LSM_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sql_fetch(
  TestDb *pTestDb, 
  void *pKey, 
  int nKey, 
  void **ppVal, 
  int *pnVal
){
  SqlDb *pDb = (SqlDb *)pTestDb;
  int rc;

  sqlite3_reset(pDb->pFetch);
  if( pKey==0 ){
    assert( ppVal==0 );
    assert( pnVal==0 );
    return LSM_OK;
  }

  sqlite3_bind_blob(pDb->pFetch, 1, pKey, nKey, SQLITE_STATIC);
  rc = sqlite3_step(pDb->pFetch);
  if( rc==SQLITE_ROW ){
    int nVal = sqlite3_column_bytes(pDb->pFetch, 0);
    u8 *aVal = (void *)sqlite3_column_blob(pDb->pFetch, 0);

    if( nVal>pDb->nAlloc ){
      free(pDb->aAlloc);
      pDb->aAlloc = (u8 *)malloc(nVal*2);
      pDb->nAlloc = nVal*2;
    }
    memcpy(pDb->aAlloc, aVal, nVal);
    *pnVal = nVal;
    *ppVal = (void *)pDb->aAlloc;
  }else{
    *pnVal = -1;
    *ppVal = 0;
  }

  rc = sqlite3_reset(pDb->pFetch);
  return rc;
}