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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  hcurArrow; int /*<<< orphan*/  hcurDivopen; int /*<<< orphan*/  hcurDivider; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetCursorPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEADER_InternalHitTest (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ HHT_ONDIVIDER ; 
 scalar_t__ HHT_ONDIVOPEN ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
HEADER_SetCursor (HEADER_INFO *infoPtr, LPARAM lParam)
{
    POINT pt;
    UINT  flags;
    INT   nItem;

    TRACE("code=0x%X  id=0x%X\n", LOWORD(lParam), HIWORD(lParam));

    GetCursorPos (&pt);
    ScreenToClient (infoPtr->hwndSelf, &pt);

    HEADER_InternalHitTest (infoPtr, &pt, &flags, &nItem);

    if (flags == HHT_ONDIVIDER)
        SetCursor (infoPtr->hcurDivider);
    else if (flags == HHT_ONDIVOPEN)
        SetCursor (infoPtr->hcurDivopen);
    else
        SetCursor (infoPtr->hcurArrow);

    return 0;
}