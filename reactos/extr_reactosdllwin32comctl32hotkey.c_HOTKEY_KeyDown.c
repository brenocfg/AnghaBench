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
typedef  scalar_t__ WORD ;
struct TYPE_4__ {scalar_t__ HotKey; scalar_t__ CurrMod; scalar_t__ InvMod; int ScanCode; scalar_t__ hwndSelf; int /*<<< orphan*/  hwndNotify; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ HOTKEY_INFO ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetDlgCtrlID (scalar_t__) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HOTKEYF_ALT ; 
 scalar_t__ HOTKEYF_CONTROL ; 
 scalar_t__ HOTKEYF_SHIFT ; 
 int /*<<< orphan*/  HOTKEY_IsCombInv (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* MAKEWORD (int,scalar_t__) ; 
 int /*<<< orphan*/  MAKEWPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VK_BACK 136 
#define  VK_CONTROL 135 
#define  VK_DELETE 134 
#define  VK_ESCAPE 133 
#define  VK_MENU 132 
#define  VK_RETURN 131 
#define  VK_SHIFT 130 
#define  VK_SPACE 129 
#define  VK_TAB 128 
 int /*<<< orphan*/  WM_COMMAND ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 
 int WS_DISABLED ; 

__attribute__((used)) static LRESULT
HOTKEY_KeyDown (HOTKEY_INFO *infoPtr, DWORD key, DWORD flags)
{
    WORD wOldHotKey;
    BYTE bOldMod;

    if (GetWindowLongW(infoPtr->hwndSelf, GWL_STYLE) & WS_DISABLED)
        return 0;

    TRACE("() Key: %d\n", key);

    wOldHotKey = infoPtr->HotKey;
    bOldMod = infoPtr->CurrMod;

    /* If any key is Pressed, we have to reset the hotkey in the control */
    infoPtr->HotKey = 0;

    switch (key)
    {
	case VK_RETURN:
	case VK_TAB:
	case VK_SPACE:
	case VK_DELETE:
	case VK_ESCAPE:
	case VK_BACK:
	    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
	    return DefWindowProcW (infoPtr->hwndSelf, WM_KEYDOWN, key, flags);

	case VK_SHIFT:
	    infoPtr->CurrMod |= HOTKEYF_SHIFT;
	    break;
	case VK_CONTROL:
	    infoPtr->CurrMod |= HOTKEYF_CONTROL;
	    break;
	case VK_MENU:
	    infoPtr->CurrMod |= HOTKEYF_ALT;
	    break;

	default:
	    if(HOTKEY_IsCombInv(infoPtr))
	        infoPtr->HotKey = MAKEWORD(key, infoPtr->InvMod);
	    else
	        infoPtr->HotKey = MAKEWORD(key, infoPtr->CurrMod);
	    infoPtr->ScanCode = flags;
	    break;
    }

    if ((wOldHotKey != infoPtr->HotKey) || (bOldMod != infoPtr->CurrMod))
    {
        InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);

        /* send EN_CHANGE notification */
        SendMessageW(infoPtr->hwndNotify, WM_COMMAND,
            MAKEWPARAM(GetDlgCtrlID(infoPtr->hwndSelf), EN_CHANGE),
            (LPARAM)infoPtr->hwndSelf);
    }

    return 0;
}