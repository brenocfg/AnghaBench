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
struct TYPE_5__ {TYPE_2__* pCsrCache; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int /*<<< orphan*/  lsmMCursorClose (TYPE_2__*,int /*<<< orphan*/ ) ; 

void lsmMCursorFreeCache(lsm_db *pDb){
  MultiCursor *p;
  MultiCursor *pNext;
  for(p=pDb->pCsrCache; p; p=pNext){
    pNext = p->pNext;
    lsmMCursorClose(p, 0);
  }
  pDb->pCsrCache = 0;
}