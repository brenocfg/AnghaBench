#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nFlags; scalar_t__ style; } ;
typedef  TYPE_1__ ME_Run ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MERF_NOJOIN ; 
 int MERF_STYLEFLAGS ; 
 int /*<<< orphan*/  TRUE ; 

BOOL ME_CanJoinRuns(const ME_Run *run1, const ME_Run *run2)
{
  if ((run1->nFlags | run2->nFlags) & MERF_NOJOIN)
    return FALSE;
  if (run1->style != run2->style)
    return FALSE;
  if ((run1->nFlags & MERF_STYLEFLAGS) != (run2->nFlags & MERF_STYLEFLAGS))
    return FALSE;
  return TRUE;
}