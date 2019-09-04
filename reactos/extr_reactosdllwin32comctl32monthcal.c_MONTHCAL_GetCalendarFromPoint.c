#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* calendars; } ;
struct TYPE_12__ {int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_10__ {int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; } ;
struct TYPE_9__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_11__ {TYPE_2__ days; TYPE_1__ title; } ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_5__ MONTHCAL_INFO ;
typedef  size_t INT ;

/* Variables and functions */
 size_t MONTHCAL_GetCalCount (TYPE_5__ const*) ; 
 scalar_t__ PtInRect (TYPE_4__*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static INT MONTHCAL_GetCalendarFromPoint(const MONTHCAL_INFO *infoPtr, const POINT *pt)
{
  RECT r;
  INT i;

  for (i = 0; i < MONTHCAL_GetCalCount(infoPtr); i++)
  {
     /* whole bounding rectangle allows some optimization to compute */
     r.left   = infoPtr->calendars[i].title.left;
     r.top    = infoPtr->calendars[i].title.top;
     r.bottom = infoPtr->calendars[i].days.bottom;
     r.right  = infoPtr->calendars[i].days.right;

     if (PtInRect(&r, *pt)) return i;
  }

  return -1;
}