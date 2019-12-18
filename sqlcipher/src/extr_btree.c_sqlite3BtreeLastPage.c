#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int nPage; } ;
struct TYPE_5__ {TYPE_4__* pBt; } ;
typedef  TYPE_1__ Btree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreePagecount (TYPE_4__*) ; 
 int sqlite3BtreeHoldsMutex (TYPE_1__*) ; 

u32 sqlite3BtreeLastPage(Btree *p){
  assert( sqlite3BtreeHoldsMutex(p) );
  assert( ((p->pBt->nPage)&0x80000000)==0 );
  return btreePagecount(p->pBt);
}