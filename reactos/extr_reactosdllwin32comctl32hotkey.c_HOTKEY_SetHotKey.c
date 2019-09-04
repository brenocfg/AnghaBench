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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  HotKey; int /*<<< orphan*/  ScanCode; } ;
typedef  TYPE_1__ HOTKEY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapVirtualKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void
HOTKEY_SetHotKey(HOTKEY_INFO *infoPtr, WORD hotKey)
{
    infoPtr->HotKey = hotKey;
    infoPtr->ScanCode = 
        MAKELPARAM(0, MapVirtualKeyW(LOBYTE(infoPtr->HotKey), 0));
    TRACE("(infoPtr=%p hotKey=%x) Modifiers: 0x%x, Virtual Key: %d\n", infoPtr,
          hotKey, HIBYTE(infoPtr->HotKey), LOBYTE(infoPtr->HotKey));
    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
}