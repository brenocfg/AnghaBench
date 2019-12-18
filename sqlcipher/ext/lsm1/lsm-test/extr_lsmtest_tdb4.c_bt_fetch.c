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
typedef  int /*<<< orphan*/  bt_cursor ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int nBuffer; int /*<<< orphan*/  pBt; int /*<<< orphan*/ * aBuffer; scalar_t__ bFastInsert; } ;
typedef  TYPE_1__ BtDb ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONTROL_FAST_INSERT_OP ; 
 int /*<<< orphan*/  BT_SEEK_EQ ; 
 int SQLITE4_INEXACT ; 
 int SQLITE4_NOTFOUND ; 
 int SQLITE4_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int sqlite4BtBegin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite4BtCommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite4BtControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite4BtCsrClose (int /*<<< orphan*/ *) ; 
 int sqlite4BtCsrData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void const**,int*) ; 
 int sqlite4BtCsrOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite4BtCsrSeek (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int sqlite4BtTransactionLevel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bt_fetch(
  TestDb *pTestDb, 
  void *pK, int nK, 
  void **ppVal, int *pnVal
){
  BtDb *p = (BtDb*)pTestDb;
  bt_cursor *pCsr = 0;
  int iLevel;
  int rc = SQLITE4_OK;

  iLevel = sqlite4BtTransactionLevel(p->pBt);
  if( iLevel==0 ){ 
    rc = sqlite4BtBegin(p->pBt, 1); 
    if( rc!=SQLITE4_OK ) return rc;
  }

  if( p->bFastInsert ) sqlite4BtControl(p->pBt, BT_CONTROL_FAST_INSERT_OP, 0);
  rc = sqlite4BtCsrOpen(p->pBt, 0, &pCsr);
  if( rc==SQLITE4_OK ){
    rc = sqlite4BtCsrSeek(pCsr, pK, nK, BT_SEEK_EQ);
    if( rc==SQLITE4_OK ){
      const void *pV = 0;
      int nV = 0;
      rc = sqlite4BtCsrData(pCsr, 0, -1, &pV, &nV);
      if( rc==SQLITE4_OK ){
        if( nV>p->nBuffer ){
          free(p->aBuffer);
          p->aBuffer = (u8*)malloc(nV*2);
          p->nBuffer = nV*2;
        }
        memcpy(p->aBuffer, pV, nV);
        *pnVal = nV;
        *ppVal = (void*)(p->aBuffer);
      }

    }else if( rc==SQLITE4_INEXACT || rc==SQLITE4_NOTFOUND ){
      *ppVal = 0;
      *pnVal = -1;
      rc = SQLITE4_OK;
    }
    sqlite4BtCsrClose(pCsr);
  }

  if( iLevel==0 ) sqlite4BtCommit(p->pBt, 0); 
  return rc;
}