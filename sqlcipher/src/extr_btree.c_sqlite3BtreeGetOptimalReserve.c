#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pBt; } ;
struct TYPE_7__ {int optimalReserve; } ;
typedef  TYPE_2__ Btree ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_2__*) ; 
 int sqlite3BtreeGetReserveNoMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_2__*) ; 

int sqlite3BtreeGetOptimalReserve(Btree *p){
  int n;
  sqlite3BtreeEnter(p);
  n = sqlite3BtreeGetReserveNoMutex(p);
#ifdef SQLITE_HAS_CODEC
  if( n<p->pBt->optimalReserve ) n = p->pBt->optimalReserve;
#endif
  sqlite3BtreeLeave(p);
  return n;
}