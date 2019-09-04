#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwStyle; scalar_t__ maxSelCount; } ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MCS_MULTISELECT ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetMaxSelCount(MONTHCAL_INFO *infoPtr, INT max)
{
  TRACE("%d\n", max);

  if(!(infoPtr->dwStyle & MCS_MULTISELECT)) return FALSE;
  if(max <= 0) return FALSE;

  infoPtr->maxSelCount = max;

  return TRUE;
}