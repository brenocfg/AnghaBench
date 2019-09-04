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
struct TYPE_4__ {scalar_t__ cxMinBand; scalar_t__ cxEffective; int fStyle; } ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  TYPE_1__ REBAR_BAND ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int RBBS_FIXEDSIZE ; 
 TYPE_1__* REBAR_GetBand (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ prev_visible (int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static REBAR_BAND *REBAR_FindBandToGrow(const REBAR_INFO *infoPtr, INT iBeginBand, INT iEndBand)
{
    INT cxMinFirstBand = 0, i;

    cxMinFirstBand = REBAR_GetBand(infoPtr, iBeginBand)->cxMinBand;

    for (i = prev_visible(infoPtr, iEndBand); i >= iBeginBand; i = prev_visible(infoPtr, i))
        if (REBAR_GetBand(infoPtr, i)->cxEffective > cxMinFirstBand &&
          !(REBAR_GetBand(infoPtr, i)->fStyle & RBBS_FIXEDSIZE))
            break;

    if (i < iBeginBand)
        for (i = prev_visible(infoPtr, iEndBand); i >= iBeginBand; i = prev_visible(infoPtr, i))
            if (REBAR_GetBand(infoPtr, i)->cxMinBand == cxMinFirstBand)
                break;

    TRACE("Extra space for row [%d..%d) should be added to band %d\n", iBeginBand, iEndBand, i);
    return REBAR_GetBand(infoPtr, i);
}