#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_12__ {scalar_t__ iXpos; scalar_t__ iYpos; scalar_t__ iScroll; TYPE_1__ hdr; scalar_t__ iDir; int /*<<< orphan*/  rcParent; } ;
struct TYPE_11__ {int dwStyle; scalar_t__ nPos; int nButtonSize; int direction; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hwndNotify; scalar_t__ hwndChild; } ;
struct TYPE_10__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ PAGER_INFO ;
typedef  TYPE_4__ NMPGSCROLL ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PAGER_SetPos (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PGF_SCROLLLEFT ; 
 scalar_t__ PGF_SCROLLUP ; 
 int /*<<< orphan*/  PGN_SCROLL ; 
 int PGS_HORZ ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 

__attribute__((used)) static void
PAGER_Scroll(PAGER_INFO* infoPtr, INT dir)
{
    NMPGSCROLL nmpgScroll;
    RECT rcWnd;

    if (infoPtr->hwndChild)
    {
        ZeroMemory (&nmpgScroll, sizeof (NMPGSCROLL));
        nmpgScroll.hdr.hwndFrom = infoPtr->hwndSelf;
        nmpgScroll.hdr.idFrom   = GetWindowLongPtrW (infoPtr->hwndSelf, GWLP_ID);
        nmpgScroll.hdr.code = PGN_SCROLL;

        GetWindowRect(infoPtr->hwndSelf, &rcWnd);
        GetClientRect(infoPtr->hwndSelf, &nmpgScroll.rcParent);
        nmpgScroll.iXpos = nmpgScroll.iYpos = 0;
        nmpgScroll.iDir = dir;

        if (infoPtr->dwStyle & PGS_HORZ)
        {
            nmpgScroll.iScroll = rcWnd.right - rcWnd.left;
            nmpgScroll.iXpos = infoPtr->nPos;
        }
        else
        {
            nmpgScroll.iScroll = rcWnd.bottom - rcWnd.top;
            nmpgScroll.iYpos = infoPtr->nPos;
        }
        nmpgScroll.iScroll -= 2*infoPtr->nButtonSize;

        SendMessageW (infoPtr->hwndNotify, WM_NOTIFY, nmpgScroll.hdr.idFrom, (LPARAM)&nmpgScroll);

        TRACE("[%p] PGN_SCROLL returns iScroll=%d\n", infoPtr->hwndSelf, nmpgScroll.iScroll);

        if (nmpgScroll.iScroll > 0)
        {
            infoPtr->direction = dir;

            if (dir == PGF_SCROLLLEFT || dir == PGF_SCROLLUP)
                PAGER_SetPos(infoPtr, infoPtr->nPos - nmpgScroll.iScroll, TRUE, TRUE);
            else
                PAGER_SetPos(infoPtr, infoPtr->nPos + nmpgScroll.iScroll, TRUE, TRUE);
        }
        else
            infoPtr->direction = -1;
    }
}