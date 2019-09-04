#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {int uBand; int /*<<< orphan*/  fStyle; int /*<<< orphan*/  dwMask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wID; } ;
struct TYPE_4__ {int fMask; int /*<<< orphan*/  fStyle; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wID; } ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  TYPE_1__ REBAR_BAND ;
typedef  TYPE_2__ NMREBAR ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int RBBIM_ID ; 
 int RBBIM_LPARAM ; 
 int RBBIM_STYLE ; 
 int /*<<< orphan*/  RBNM_ID ; 
 int /*<<< orphan*/  RBNM_LPARAM ; 
 int /*<<< orphan*/  RBNM_STYLE ; 
 TYPE_1__* REBAR_GetBand (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  REBAR_Notify (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static INT
REBAR_Notify_NMREBAR (const REBAR_INFO *infoPtr, UINT uBand, UINT code)
{
    NMREBAR notify_rebar;

    notify_rebar.dwMask = 0;
    if (uBand != -1) {
	REBAR_BAND *lpBand = REBAR_GetBand(infoPtr, uBand);

	if (lpBand->fMask & RBBIM_ID) {
	    notify_rebar.dwMask |= RBNM_ID;
	    notify_rebar.wID = lpBand->wID;
	}
	if (lpBand->fMask & RBBIM_LPARAM) {
	    notify_rebar.dwMask |= RBNM_LPARAM;
	    notify_rebar.lParam = lpBand->lParam;
	}
	if (lpBand->fMask & RBBIM_STYLE) {
	    notify_rebar.dwMask |= RBNM_STYLE;
	    notify_rebar.fStyle = lpBand->fStyle;
	}
    }
    notify_rebar.uBand = uBand;
    return REBAR_Notify ((NMHDR *)&notify_rebar, infoPtr, code);
}