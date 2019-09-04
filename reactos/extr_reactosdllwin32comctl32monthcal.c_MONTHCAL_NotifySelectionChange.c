#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ wDayOfWeek; } ;
struct TYPE_7__ {scalar_t__ wDayOfWeek; } ;
struct TYPE_10__ {int dwStyle; int /*<<< orphan*/  hwndNotify; TYPE_5__ maxSel; TYPE_1__ minSel; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_8__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_9__ {TYPE_2__ nmhdr; TYPE_5__ stSelEnd; TYPE_1__ stSelStart; } ;
typedef  TYPE_3__ NMSELCHANGE ;
typedef  TYPE_4__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCN_SELCHANGE ; 
 int MCS_MULTISELECT ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 TYPE_5__ st_null ; 

__attribute__((used)) static inline void MONTHCAL_NotifySelectionChange(const MONTHCAL_INFO *infoPtr)
{
    NMSELCHANGE nmsc;

    nmsc.nmhdr.hwndFrom = infoPtr->hwndSelf;
    nmsc.nmhdr.idFrom   = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
    nmsc.nmhdr.code     = MCN_SELCHANGE;
    nmsc.stSelStart     = infoPtr->minSel;
    nmsc.stSelStart.wDayOfWeek = 0;
    if(infoPtr->dwStyle & MCS_MULTISELECT){
        nmsc.stSelEnd = infoPtr->maxSel;
        nmsc.stSelEnd.wDayOfWeek = 0;
    }
    else
        nmsc.stSelEnd = st_null;

    SendMessageW(infoPtr->hwndNotify, WM_NOTIFY, nmsc.nmhdr.idFrom, (LPARAM)&nmsc);
}