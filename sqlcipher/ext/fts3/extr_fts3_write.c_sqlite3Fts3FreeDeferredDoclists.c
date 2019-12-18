#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pDeferred; } ;
struct TYPE_4__ {scalar_t__ pList; struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ Fts3DeferredToken ;
typedef  TYPE_2__ Fts3Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  fts3PendingListDelete (scalar_t__) ; 

void sqlite3Fts3FreeDeferredDoclists(Fts3Cursor *pCsr){
  Fts3DeferredToken *pDef;
  for(pDef=pCsr->pDeferred; pDef; pDef=pDef->pNext){
    fts3PendingListDelete(pDef->pList);
    pDef->pList = 0;
  }
}