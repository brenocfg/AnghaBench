#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * bufBase; int /*<<< orphan*/ * bufLim; } ;
struct TYPE_6__ {scalar_t__ (* Alloc ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CRangeEnc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int RC_BUF_SIZE ; 
 scalar_t__ stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static int RangeEnc_Alloc(CRangeEnc *p, ISzAlloc *alloc)
{
  if (p->bufBase == 0)
  {
    p->bufBase = (Byte *)alloc->Alloc(alloc, RC_BUF_SIZE);
    if (p->bufBase == 0)
      return 0;
    p->bufLim = p->bufBase + RC_BUF_SIZE;
  }
  return 1;
}