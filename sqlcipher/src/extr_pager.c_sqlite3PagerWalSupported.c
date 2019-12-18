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
struct TYPE_6__ {int iVersion; scalar_t__ xShmMap; } ;
typedef  TYPE_2__ sqlite3_io_methods ;
struct TYPE_7__ {scalar_t__ exclusiveMode; scalar_t__ noLock; TYPE_1__* fd; } ;
struct TYPE_5__ {TYPE_2__* pMethods; } ;
typedef  TYPE_3__ Pager ;

/* Variables and functions */

int sqlite3PagerWalSupported(Pager *pPager){
  const sqlite3_io_methods *pMethods = pPager->fd->pMethods;
  if( pPager->noLock ) return 0;
  return pPager->exclusiveMode || (pMethods->iVersion>=2 && pMethods->xShmMap);
}