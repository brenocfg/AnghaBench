#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
struct TYPE_5__ {TYPE_2__* pCursor; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ BtShared ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidateOverflowCache (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void invalidateAllOverflowCache(BtShared *pBt){
  BtCursor *p;
  assert( sqlite3_mutex_held(pBt->mutex) );
  for(p=pBt->pCursor; p; p=p->pNext){
    invalidateOverflowCache(p);
  }
}