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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int /*<<< orphan*/ ** apScan; } ;
typedef  TYPE_1__ SqlDb ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sql_scan(
  TestDb *pTestDb,
  void *pCtx,
  int bReverse,
  void *pFirst, int nFirst,
  void *pLast, int nLast,
  void (*xCallback)(void *, void *, int , void *, int)
){
  SqlDb *pDb = (SqlDb *)pTestDb;
  sqlite3_stmt *pScan;

  assert( bReverse==1 || bReverse==0 );
  pScan = pDb->apScan[(pFirst==0) + (pLast==0)*2 + bReverse*4];

  if( pFirst ) sqlite3_bind_blob(pScan, 1, pFirst, nFirst, SQLITE_STATIC);
  if( pLast ) sqlite3_bind_blob(pScan, 2, pLast, nLast, SQLITE_STATIC);

  while( SQLITE_ROW==sqlite3_step(pScan) ){
    void *pKey; int nKey;
    void *pVal; int nVal;

    nKey = sqlite3_column_bytes(pScan, 0);
    pKey = (void *)sqlite3_column_blob(pScan, 0);
    nVal = sqlite3_column_bytes(pScan, 1);
    pVal = (void *)sqlite3_column_blob(pScan, 1);

    xCallback(pCtx, pKey, nKey, pVal, nVal);
  }
  return sqlite3_reset(pScan);
}