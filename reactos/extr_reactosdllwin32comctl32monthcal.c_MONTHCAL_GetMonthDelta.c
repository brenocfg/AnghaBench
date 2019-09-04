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
struct TYPE_4__ {scalar_t__ delta; } ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  scalar_t__ LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GMR_VISIBLE ; 
 scalar_t__ MONTHCAL_GetMonthRange (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static LRESULT
MONTHCAL_GetMonthDelta(const MONTHCAL_INFO *infoPtr)
{
  TRACE("\n");

  if(infoPtr->delta)
    return infoPtr->delta;

  return MONTHCAL_GetMonthRange(infoPtr, GMR_VISIBLE, NULL);
}