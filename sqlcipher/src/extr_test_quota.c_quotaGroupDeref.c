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
struct TYPE_8__ {scalar_t__ iLimit; int /*<<< orphan*/  pArg; int /*<<< orphan*/  (* xDestroy ) (int /*<<< orphan*/ ) ;TYPE_1__** ppPrev; TYPE_1__* pNext; } ;
typedef  TYPE_2__ quotaGroup ;
struct TYPE_7__ {struct TYPE_7__** ppPrev; } ;

/* Variables and functions */
 scalar_t__ quotaGroupOpenFileCount (TYPE_2__*) ; 
 int /*<<< orphan*/  quotaRemoveAllFiles (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void quotaGroupDeref(quotaGroup *pGroup){
  if( pGroup->iLimit==0 && quotaGroupOpenFileCount(pGroup)==0 ){
    quotaRemoveAllFiles(pGroup);
    *pGroup->ppPrev = pGroup->pNext;
    if( pGroup->pNext ) pGroup->pNext->ppPrev = pGroup->ppPrev;
    if( pGroup->xDestroy ) pGroup->xDestroy(pGroup->pArg);
    sqlite3_free(pGroup);
  }
}