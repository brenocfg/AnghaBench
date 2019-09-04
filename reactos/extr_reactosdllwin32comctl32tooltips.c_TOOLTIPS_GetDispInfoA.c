#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_11__ {scalar_t__ lpszText; scalar_t__ szText; int uFlags; int /*<<< orphan*/  hinst; TYPE_1__ hdr; int /*<<< orphan*/  lParam; } ;
struct TYPE_10__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_9__ {int uFlags; int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; int /*<<< orphan*/ * lpszText; int /*<<< orphan*/  hinst; int /*<<< orphan*/  lParam; } ;
typedef  TYPE_2__ TTTOOL_INFO ;
typedef  TYPE_3__ TOOLTIPS_INFO ;
typedef  TYPE_4__ NMTTDISPINFOA ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFOTIPSIZE ; 
 scalar_t__ IS_INTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 scalar_t__ LPSTR_TEXTCALLBACKA ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_GetPtrAtoW (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Str_SetPtrW (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int TTF_DI_SETITEM ; 
 int /*<<< orphan*/  TTN_GETDISPINFOA ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 

__attribute__((used)) static void TOOLTIPS_GetDispInfoA(const TOOLTIPS_INFO *infoPtr, TTTOOL_INFO *toolPtr, WCHAR *buffer)
{
    NMTTDISPINFOA ttnmdi;

    /* fill NMHDR struct */
    ZeroMemory (&ttnmdi, sizeof(NMTTDISPINFOA));
    ttnmdi.hdr.hwndFrom = infoPtr->hwndSelf;
    ttnmdi.hdr.idFrom = toolPtr->uId;
    ttnmdi.hdr.code = TTN_GETDISPINFOA; /* == TTN_NEEDTEXTA */
    ttnmdi.lpszText = ttnmdi.szText;
    ttnmdi.uFlags = toolPtr->uFlags;
    ttnmdi.lParam = toolPtr->lParam;

    TRACE("hdr.idFrom = %lx\n", ttnmdi.hdr.idFrom);
    SendMessageW(toolPtr->hwnd, WM_NOTIFY, toolPtr->uId, (LPARAM)&ttnmdi);

    if (IS_INTRESOURCE(ttnmdi.lpszText)) {
        LoadStringW(ttnmdi.hinst, LOWORD(ttnmdi.lpszText),
               buffer, INFOTIPSIZE);
        if (ttnmdi.uFlags & TTF_DI_SETITEM) {
            toolPtr->hinst = ttnmdi.hinst;
            toolPtr->lpszText = (LPWSTR)ttnmdi.lpszText;
        }
    }
    else if (ttnmdi.lpszText == 0) {
        buffer[0] = '\0';
    }
    else if (ttnmdi.lpszText != LPSTR_TEXTCALLBACKA) {
        Str_GetPtrAtoW(ttnmdi.lpszText, buffer, INFOTIPSIZE);
        if (ttnmdi.uFlags & TTF_DI_SETITEM) {
            toolPtr->hinst = 0;
            toolPtr->lpszText = NULL;
            Str_SetPtrW(&toolPtr->lpszText, buffer);
        }
    }
    else {
        ERR("recursive text callback\n");
        buffer[0] = '\0';
    }

    /* no text available - try calling parent instead as per native */
    /* FIXME: Unsure if SETITEM should save the value or not        */
    if (buffer[0] == 0x00) {

        SendMessageW(GetParent(toolPtr->hwnd), WM_NOTIFY, toolPtr->uId, (LPARAM)&ttnmdi);

        if (IS_INTRESOURCE(ttnmdi.lpszText)) {
            LoadStringW(ttnmdi.hinst, LOWORD(ttnmdi.lpszText),
                   buffer, INFOTIPSIZE);
        } else if (ttnmdi.lpszText &&
                   ttnmdi.lpszText != LPSTR_TEXTCALLBACKA) {
            Str_GetPtrAtoW(ttnmdi.lpszText, buffer, INFOTIPSIZE);
        }
    }
}