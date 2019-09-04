#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ wYear; int wMonth; int wDay; int wHour; int wMinute; int wSecond; int wMilliseconds; } ;
struct TYPE_9__ {int dwStyle; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hwndCheckbut; void* dateValid; TYPE_1__ date; int /*<<< orphan*/  hMonthCal; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_2__ DATETIME_INFO ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETCHECK ; 
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  BST_UNCHECKED ; 
 int /*<<< orphan*/  DATETIME_IsDateInValidRange (TYPE_2__*,TYPE_1__ const*) ; 
 int DTS_SHOWNONE ; 
 void* FALSE ; 
 scalar_t__ GDT_NONE ; 
 scalar_t__ GDT_VALID ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  MCM_SETCURSEL ; 
 int /*<<< orphan*/  MONTHCAL_CalculateDayOfWeek (TYPE_1__*,void*) ; 
 int MONTHCAL_MonthLength (int,scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int,int,int,int) ; 
 void* TRUE ; 

__attribute__((used)) static BOOL
DATETIME_SetSystemTime (DATETIME_INFO *infoPtr, DWORD flag, const SYSTEMTIME *systime)
{
    if (!systime) return FALSE;

    TRACE("%04d/%02d/%02d %02d:%02d:%02d\n",
          systime->wYear, systime->wMonth, systime->wDay,
          systime->wHour, systime->wMinute, systime->wSecond);

    if (flag == GDT_VALID) {
        if (systime->wYear == 0 ||
            systime->wMonth < 1 || systime->wMonth > 12 ||
            systime->wDay < 1 ||
            systime->wDay > MONTHCAL_MonthLength(systime->wMonth, systime->wYear) ||
            systime->wHour > 23 ||
            systime->wMinute > 59 ||
            systime->wSecond > 59 ||
            systime->wMilliseconds > 999
           )
            return FALSE;

        /* Windows returns true if the date is valid but outside the limits set */
        if (!DATETIME_IsDateInValidRange(infoPtr, systime))
            return TRUE;

        infoPtr->dateValid = TRUE;
        infoPtr->date = *systime;
        /* always store a valid day of week */
        MONTHCAL_CalculateDayOfWeek(&infoPtr->date, TRUE);

        SendMessageW (infoPtr->hMonthCal, MCM_SETCURSEL, 0, (LPARAM)(&infoPtr->date));
        SendMessageW (infoPtr->hwndCheckbut, BM_SETCHECK, BST_CHECKED, 0);
    } else if ((infoPtr->dwStyle & DTS_SHOWNONE) && (flag == GDT_NONE)) {
        infoPtr->dateValid = FALSE;
        SendMessageW (infoPtr->hwndCheckbut, BM_SETCHECK, BST_UNCHECKED, 0);
    }
    else
        return FALSE;

    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
    return TRUE;
}