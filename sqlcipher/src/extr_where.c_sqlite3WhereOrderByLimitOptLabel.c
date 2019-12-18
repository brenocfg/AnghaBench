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
struct TYPE_4__ {scalar_t__ addrNxt; } ;
typedef  TYPE_1__ WhereLevel ;
struct TYPE_5__ {int iContinue; int nLevel; TYPE_1__* a; int /*<<< orphan*/  bOrderedInnerLoop; } ;
typedef  TYPE_2__ WhereInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int sqlite3WhereOrderByLimitOptLabel(WhereInfo *pWInfo){
  WhereLevel *pInner;
  if( !pWInfo->bOrderedInnerLoop ){
    /* The ORDER BY LIMIT optimization does not apply.  Jump to the 
    ** continuation of the inner-most loop. */
    return pWInfo->iContinue;
  }
  pInner = &pWInfo->a[pWInfo->nLevel-1];
  assert( pInner->addrNxt!=0 );
  return pInner->addrNxt;
}