#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int UINT ;
struct TYPE_12__ {struct TYPE_12__* lpText; scalar_t__ hwndChild; } ;
struct TYPE_11__ {int uNumBands; int /*<<< orphan*/  bands; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ REBAR_BAND ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DPA_DeletePtr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  RBN_DELETEDBAND ; 
 int /*<<< orphan*/  RBN_DELETINGBAND ; 
 TYPE_2__* REBAR_GetBand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  REBAR_Layout (TYPE_1__*) ; 
 int /*<<< orphan*/  REBAR_Notify_NMREBAR (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_ValidateBand (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_DeleteBand (REBAR_INFO *infoPtr, WPARAM wParam)
{
    UINT uBand = (UINT)wParam;
    REBAR_BAND *lpBand;

    if (uBand >= infoPtr->uNumBands)
	return FALSE;

    TRACE("deleting band %u!\n", uBand);
    lpBand = REBAR_GetBand(infoPtr, uBand);
    REBAR_Notify_NMREBAR (infoPtr, uBand, RBN_DELETINGBAND);
    /* TODO: a return of 1 should probably cancel the deletion */

    if (lpBand->hwndChild)
        ShowWindow(lpBand->hwndChild, SW_HIDE);
    Free(lpBand->lpText);
    Free(lpBand);

    infoPtr->uNumBands--;
    DPA_DeletePtr(infoPtr->bands, uBand);

    REBAR_Notify_NMREBAR (infoPtr, -1, RBN_DELETEDBAND);

    /* if only 1 band left the re-validate to possible eliminate gripper */
    if (infoPtr->uNumBands == 1)
      REBAR_ValidateBand (infoPtr, REBAR_GetBand(infoPtr, 0));

    REBAR_Layout(infoPtr);

    return TRUE;
}