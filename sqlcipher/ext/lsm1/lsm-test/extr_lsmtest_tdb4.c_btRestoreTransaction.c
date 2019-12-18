#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pBt; } ;
typedef  TYPE_1__ BtDb ;

/* Variables and functions */
 int SQLITE4_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite4BtCommit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite4BtRollback (int /*<<< orphan*/ ,int) ; 
 int sqlite4BtTransactionLevel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btRestoreTransaction(BtDb *p, int iLevel, int rcin){
  int rc = rcin;
  if( iLevel>=0 ){
    if( rc==SQLITE4_OK ){
      rc = sqlite4BtCommit(p->pBt, iLevel);
    }else{
      sqlite4BtRollback(p->pBt, iLevel);
    }
    assert( iLevel==sqlite4BtTransactionLevel(p->pBt) );
  }
  return rc;
}