#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int wDay; } ;
struct TYPE_10__ {int dwStyle; int /*<<< orphan*/  monthdayState; int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_8__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_9__ {int cDayState; int /*<<< orphan*/ * prgDayState; TYPE_1__ nmhdr; TYPE_7__ stStart; } ;
typedef  TYPE_2__ NMDAYSTATE ;
typedef  int /*<<< orphan*/  MONTHDAYSTATE ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  GMR_DAYSTATE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCN_GETDAYSTATE ; 
 int MCS_DAYSTATE ; 
 int /*<<< orphan*/  MONTHCAL_GetMinDate (TYPE_3__*,TYPE_7__*) ; 
 int MONTHCAL_GetMonthRange (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void MONTHCAL_NotifyDayState(MONTHCAL_INFO *infoPtr)
{
  MONTHDAYSTATE *state;
  NMDAYSTATE nmds;

  if (!(infoPtr->dwStyle & MCS_DAYSTATE)) return;

  nmds.nmhdr.hwndFrom = infoPtr->hwndSelf;
  nmds.nmhdr.idFrom   = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
  nmds.nmhdr.code     = MCN_GETDAYSTATE;
  nmds.cDayState      = MONTHCAL_GetMonthRange(infoPtr, GMR_DAYSTATE, 0);
  nmds.prgDayState    = state = heap_alloc_zero(nmds.cDayState * sizeof(MONTHDAYSTATE));

  MONTHCAL_GetMinDate(infoPtr, &nmds.stStart);
  nmds.stStart.wDay = 1;

  SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, nmds.nmhdr.idFrom, (LPARAM)&nmds);
  memcpy(infoPtr->monthdayState, nmds.prgDayState,
      MONTHCAL_GetMonthRange(infoPtr, GMR_DAYSTATE, 0)*sizeof(MONTHDAYSTATE));

  heap_free(state);
}