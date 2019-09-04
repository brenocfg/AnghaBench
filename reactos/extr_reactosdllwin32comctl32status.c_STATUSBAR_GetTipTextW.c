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
typedef  scalar_t__ WCHAR ;
struct TYPE_5__ {scalar_t__ hwndToolTip; int /*<<< orphan*/  Self; } ;
struct TYPE_4__ {int cbSize; scalar_t__* lpszText; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int INFOTIPSIZE ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TTM_GETTEXTW ; 
 int /*<<< orphan*/  lstrcpynW (scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
STATUSBAR_GetTipTextW (const STATUS_INFO *infoPtr, INT id, LPWSTR tip, INT size)
{
    TRACE("\n");
    if (tip) {
        WCHAR buf[INFOTIPSIZE];
        buf[0]=0;

	if (infoPtr->hwndToolTip) {
	    TTTOOLINFOW ti;
	    ti.cbSize = sizeof(TTTOOLINFOW);
	    ti.hwnd = infoPtr->Self;
	    ti.uId = id;
            ti.lpszText = buf;
	    SendMessageW(infoPtr->hwndToolTip, TTM_GETTEXTW, 0, (LPARAM)&ti);
	}
	lstrcpynW(tip, buf, size);
    }

    return 0;
}