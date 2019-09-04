#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bottom; int top; } ;
struct TYPE_8__ {int cyChild; int fStyle; int /*<<< orphan*/  cyMinBand; int /*<<< orphan*/  fDraw; int /*<<< orphan*/  cyMaxChild; scalar_t__ hwndChild; TYPE_1__ rcBand; } ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NTF_INVALIDATE ; 
 int RBBS_VARIABLEHEIGHT ; 
 int REBARSPACE (TYPE_2__*) ; 
 TYPE_2__* REBAR_GetBand (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int next_visible (int /*<<< orphan*/  const*,int) ; 
 int round_child_height (TYPE_2__*,int) ; 
 int /*<<< orphan*/  update_min_band_height (int /*<<< orphan*/  const*,TYPE_2__*) ; 

__attribute__((used)) static int
REBAR_SizeChildrenToHeight(const REBAR_INFO *infoPtr, int iBeginBand, int iEndBand, int extra, BOOL *fChanged)
{
    int cyBandsOld;
    int cyBandsNew = 0;
    int i;

    TRACE("[%d;%d) by %d\n", iBeginBand, iEndBand, extra);

    cyBandsOld = REBAR_GetBand(infoPtr, iBeginBand)->rcBand.bottom -
                 REBAR_GetBand(infoPtr, iBeginBand)->rcBand.top;
    for (i = iBeginBand; i < iEndBand; i = next_visible(infoPtr, i))
    {
        REBAR_BAND *lpBand = REBAR_GetBand(infoPtr, i);
        int cyMaxChild = cyBandsOld - REBARSPACE(lpBand) + extra;
        int cyChild = round_child_height(lpBand, cyMaxChild);

        if (lpBand->hwndChild && cyChild != lpBand->cyChild && (lpBand->fStyle & RBBS_VARIABLEHEIGHT))
        {
            TRACE("Resizing %d: %d -> %d [%d]\n", i, lpBand->cyChild, cyChild, lpBand->cyMaxChild);
            *fChanged = TRUE;
            lpBand->cyChild = cyChild;
            lpBand->fDraw |= NTF_INVALIDATE;
            update_min_band_height(infoPtr, lpBand);
        }
        cyBandsNew = max(cyBandsNew, lpBand->cyMinBand);
    }
    return cyBandsNew - cyBandsOld;
}