#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bt_cursor ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_4__ {int /*<<< orphan*/  pBt; scalar_t__ bFastInsert; } ;
typedef  TYPE_1__ BtDb ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONTROL_FAST_INSERT_OP ; 
 int /*<<< orphan*/  BT_SEEK_GE ; 
 int MIN (int,int) ; 
 int SQLITE4_INEXACT ; 
 int SQLITE4_NOTFOUND ; 
 int SQLITE4_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int btMinTransaction (TYPE_1__*,int,int*) ; 
 int btRestoreTransaction (TYPE_1__*,int,int) ; 
 int memcmp (void*,void const*,int) ; 
 int /*<<< orphan*/  sqlite4BtControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite4BtCsrClose (int /*<<< orphan*/ *) ; 
 int sqlite4BtCsrKey (int /*<<< orphan*/ *,void const**,int*) ; 
 int sqlite4BtCsrNext (int /*<<< orphan*/ *) ; 
 int sqlite4BtCsrOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite4BtCsrSeek (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int sqlite4BtDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt_delete_range(
  TestDb *pTestDb, 
  void *pKey1, int nKey1,
  void *pKey2, int nKey2
){
  BtDb *p = (BtDb*)pTestDb;
  bt_cursor *pCsr = 0;
  int rc = SQLITE4_OK;
  int iLevel;

  rc = btMinTransaction(p, 2, &iLevel);
  if( rc==SQLITE4_OK ){
    if( p->bFastInsert ) sqlite4BtControl(p->pBt, BT_CONTROL_FAST_INSERT_OP, 0);
    rc = sqlite4BtCsrOpen(p->pBt, 0, &pCsr);
  }
  while( rc==SQLITE4_OK ){
    const void *pK;
    int n;
    int nCmp;
    int res;

    rc = sqlite4BtCsrSeek(pCsr, pKey1, nKey1, BT_SEEK_GE);
    if( rc==SQLITE4_INEXACT ) rc = SQLITE4_OK;
    if( rc!=SQLITE4_OK ) break;

    rc = sqlite4BtCsrKey(pCsr, &pK, &n);
    if( rc!=SQLITE4_OK ) break;

    nCmp = MIN(n, nKey1);
    res = memcmp(pKey1, pK, nCmp);
    assert( res<0 || (res==0 && nKey1<=n) );
    if( res==0 && nKey1==n ){
      rc = sqlite4BtCsrNext(pCsr);
      if( rc!=SQLITE4_OK ) break;
      rc = sqlite4BtCsrKey(pCsr, &pK, &n);
      if( rc!=SQLITE4_OK ) break;
    }

    nCmp = MIN(n, nKey2);
    res = memcmp(pKey2, pK, nCmp);
    if( res<0 || (res==0 && nKey2<=n) ) break;
    
    rc = sqlite4BtDelete(pCsr);
  }
  if( rc==SQLITE4_NOTFOUND ) rc = SQLITE4_OK;

  sqlite4BtCsrClose(pCsr);

  rc = btRestoreTransaction(p, iLevel, rc);
  return rc;
}