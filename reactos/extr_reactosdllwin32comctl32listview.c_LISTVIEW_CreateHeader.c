#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int dwStyle; scalar_t__ himlSmall; scalar_t__ hwndHeader; scalar_t__ hFont; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  int INT ;
typedef  scalar_t__ HINSTANCE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CreateWindowW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDM_SETIMAGELIST ; 
 int /*<<< orphan*/  HDM_SETUNICODEFORMAT ; 
 int HDS_BUTTONS ; 
 int HDS_DRAGDROP ; 
 int HDS_FULLDRAG ; 
 int HDS_HIDDEN ; 
 int HDS_HORZ ; 
 int /*<<< orphan*/  LISTVIEW_UpdateSize (TYPE_1__*) ; 
 int LVS_NOCOLUMNHEADER ; 
 int LVS_NOSORTHEADER ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WC_HEADERW ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CHILD ; 

__attribute__((used)) static INT LISTVIEW_CreateHeader(LISTVIEW_INFO *infoPtr)
{
    DWORD dFlags = WS_CHILD | HDS_HORZ | HDS_FULLDRAG | HDS_DRAGDROP;
    HINSTANCE hInst;

    if (infoPtr->hwndHeader) return 0;

    TRACE("Creating header for list %p\n", infoPtr->hwndSelf);

    /* setup creation flags */
    dFlags |= (LVS_NOSORTHEADER & infoPtr->dwStyle) ? 0 : HDS_BUTTONS;
    dFlags |= (LVS_NOCOLUMNHEADER & infoPtr->dwStyle) ? HDS_HIDDEN : 0;

    hInst = (HINSTANCE)GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_HINSTANCE);

    /* create header */
    infoPtr->hwndHeader = CreateWindowW(WC_HEADERW, NULL, dFlags,
      0, 0, 0, 0, infoPtr->hwndSelf, NULL, hInst, NULL);
    if (!infoPtr->hwndHeader) return -1;

    /* set header unicode format */
    SendMessageW(infoPtr->hwndHeader, HDM_SETUNICODEFORMAT, TRUE, 0);

    /* set header font */
    SendMessageW(infoPtr->hwndHeader, WM_SETFONT, (WPARAM)infoPtr->hFont, TRUE);

    /* set header image list */
    if (infoPtr->himlSmall)
        SendMessageW(infoPtr->hwndHeader, HDM_SETIMAGELIST, 0, (LPARAM)infoPtr->himlSmall);

    LISTVIEW_UpdateSize(infoPtr);

    return 0;
}