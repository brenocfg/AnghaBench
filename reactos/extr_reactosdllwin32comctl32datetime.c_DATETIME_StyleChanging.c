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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_3__ {int styleOld; int styleNew; } ;
typedef  TYPE_1__ STYLESTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  DATETIME_INFO ;

/* Variables and functions */
 int DTS_SHOWNONE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static LRESULT
DATETIME_StyleChanging(DATETIME_INFO *infoPtr, WPARAM wStyleType, STYLESTRUCT *lpss)
{
    TRACE("(styletype=%lx, styleOld=0x%08x, styleNew=0x%08x)\n",
          wStyleType, lpss->styleOld, lpss->styleNew);

    /* block DTS_SHOWNONE change */
    if ((lpss->styleNew ^ lpss->styleOld) & DTS_SHOWNONE)
    {
        if (lpss->styleOld & DTS_SHOWNONE)
            lpss->styleNew |= DTS_SHOWNONE;
        else
            lpss->styleNew &= ~DTS_SHOWNONE;
    }

    return 0;
}