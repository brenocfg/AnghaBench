#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bt_db ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ TestDb ;
struct TYPE_7__ {int /*<<< orphan*/ * pBt; } ;
struct TYPE_5__ {scalar_t__ xClose; } ;
typedef  TYPE_3__ BtDb ;

/* Variables and functions */
 scalar_t__ bt_close ; 

bt_db *tdb_bt(TestDb *pDb){
  if( pDb->pMethods->xClose==bt_close ){
    return ((BtDb *)pDb)->pBt;
  }
  return 0;
}