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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {TYPE_3__* pFKey; } ;
typedef  TYPE_1__ Table ;
struct TYPE_7__ {scalar_t__ isDeferred; } ;
struct TYPE_6__ {TYPE_1__* pNewTable; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ FKey ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void sqlite3DeferForeignKey(Parse *pParse, int isDeferred){
#ifndef SQLITE_OMIT_FOREIGN_KEY
  Table *pTab;
  FKey *pFKey;
  if( (pTab = pParse->pNewTable)==0 || (pFKey = pTab->pFKey)==0 ) return;
  assert( isDeferred==0 || isDeferred==1 ); /* EV: R-30323-21917 */
  pFKey->isDeferred = (u8)isDeferred;
#endif
}