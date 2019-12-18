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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_4__ {int /*<<< orphan*/  pBt; scalar_t__ bFastInsert; } ;
typedef  TYPE_1__ BtDb ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONTROL_FAST_INSERT_OP ; 
 int SQLITE4_OK ; 
 int btMinTransaction (TYPE_1__*,int,int*) ; 
 int btRestoreTransaction (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  sqlite4BtControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite4BtReplace (int /*<<< orphan*/ ,void*,int,void*,int) ; 

__attribute__((used)) static int bt_write(TestDb *pTestDb, void *pK, int nK, void *pV, int nV){
  BtDb *p = (BtDb*)pTestDb;
  int iLevel;
  int rc;

  rc = btMinTransaction(p, 2, &iLevel);
  if( rc==SQLITE4_OK ){
    if( p->bFastInsert ) sqlite4BtControl(p->pBt, BT_CONTROL_FAST_INSERT_OP, 0);
    rc = sqlite4BtReplace(p->pBt, pK, nK, pV, nV);
    rc = btRestoreTransaction(p, iLevel, rc);
  }
  return rc;
}