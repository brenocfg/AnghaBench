#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UPDOWN_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_DECR ; 
 int /*<<< orphan*/  FLAG_INCR ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDOWN_GetArrowRect (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT UPDOWN_GetArrowFromPoint (const UPDOWN_INFO *infoPtr, RECT *rect, POINT pt)
{
    UPDOWN_GetArrowRect (infoPtr, rect, FLAG_INCR);
    if(PtInRect(rect, pt)) return FLAG_INCR;

    UPDOWN_GetArrowRect (infoPtr, rect, FLAG_DECR);
    if(PtInRect(rect, pt)) return FLAG_DECR;

    return 0;
}