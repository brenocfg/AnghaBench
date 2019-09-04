#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_17__ {scalar_t__ cbSize; int fMask; scalar_t__ lpText; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpText; } ;
struct TYPE_15__ {scalar_t__ uNumBands; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  TYPE_3__ REBARBANDINFOW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RBBIM_CHILDSIZE ; 
 int RBBIM_IMAGE ; 
 int RBBIM_SIZE ; 
 int RBBIM_STYLE ; 
 int RBBIM_TEXT ; 
 scalar_t__ REBARBANDINFOA_V3_SIZE ; 
 int REBAR_CommonSetupBand (int /*<<< orphan*/ ,TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  REBAR_DumpBand (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_DumpBandInfo (TYPE_3__ const*) ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  REBAR_Layout (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_ValidateBand (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ REBAR_strdifW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Str_SetPtrAtoW (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_SetPtrW (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_SetBandInfoT(REBAR_INFO *infoPtr, INT iBand, const REBARBANDINFOW *lprbbi, BOOL bUnicode)
{
    REBAR_BAND *lpBand;
    UINT uChanged;

    if (!lprbbi || lprbbi->cbSize < REBARBANDINFOA_V3_SIZE)
	return FALSE;

    if (iBand >= infoPtr->uNumBands)
	return FALSE;

    TRACE("index %d\n", iBand);
    REBAR_DumpBandInfo (lprbbi);

    /* set band information */
    lpBand = REBAR_GetBand(infoPtr, iBand);

    uChanged = REBAR_CommonSetupBand (infoPtr->hwndSelf, lprbbi, lpBand);
    if (lprbbi->fMask & RBBIM_TEXT) {
        LPWSTR wstr = NULL;
        if (bUnicode)
            Str_SetPtrW(&wstr, lprbbi->lpText);
        else
            Str_SetPtrAtoW(&wstr, (LPSTR)lprbbi->lpText);

        if (REBAR_strdifW(wstr, lpBand->lpText)) {
            Free(lpBand->lpText);
            lpBand->lpText = wstr;
            uChanged |= RBBIM_TEXT;
        }
        else
            Free(wstr);
    }

    REBAR_ValidateBand (infoPtr, lpBand);

    REBAR_DumpBand (infoPtr);

    if (uChanged & (RBBIM_CHILDSIZE | RBBIM_SIZE | RBBIM_STYLE | RBBIM_IMAGE)) {
	  REBAR_Layout(infoPtr);
	  InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
    }

    return TRUE;
}