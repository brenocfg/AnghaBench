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
struct TYPE_5__ {int /*<<< orphan*/  code; int /*<<< orphan*/  idFrom; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_4__ {scalar_t__ simple; int /*<<< orphan*/  Self; int /*<<< orphan*/  Notify; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ NMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBN_SIMPLEMODECHANGE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static BOOL
STATUSBAR_Simple (STATUS_INFO *infoPtr, BOOL simple)
{
    NMHDR  nmhdr;

    TRACE("(simple=%d)\n", simple);
    if (infoPtr->simple == simple) /* no need to change */
	return TRUE;

    infoPtr->simple = simple;

    /* send notification */
    nmhdr.hwndFrom = infoPtr->Self;
    nmhdr.idFrom = GetWindowLongPtrW (infoPtr->Self, GWLP_ID);
    nmhdr.code = SBN_SIMPLEMODECHANGE;
    SendMessageW (infoPtr->Notify, WM_NOTIFY, 0, (LPARAM)&nmhdr);
    InvalidateRect(infoPtr->Self, NULL, FALSE);
    return TRUE;
}