#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_3__ {int /*<<< orphan*/  nNotifyFormat; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HEADER_INFO ;

/* Variables and functions */
#define  NF_QUERY 129 
#define  NF_REQUERY 128 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 

__attribute__((used)) static LRESULT
HEADER_NotifyFormat (HEADER_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
    switch (lParam)
    {
	case NF_QUERY:
	    return infoPtr->nNotifyFormat;

	case NF_REQUERY:
	    infoPtr->nNotifyFormat =
		SendMessageW ((HWND)wParam, WM_NOTIFYFORMAT,
                             (WPARAM)infoPtr->hwndSelf, NF_QUERY);
	    return infoPtr->nNotifyFormat;
    }

    return 0;
}