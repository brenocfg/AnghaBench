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
struct TYPE_3__ {int /*<<< orphan*/ * hEdit; int /*<<< orphan*/  hSelf; } ;
typedef  TYPE_1__* PEDIT_WND_INFO ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int ES_AUTOHSCROLL ; 
 int ES_AUTOVSCROLL ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetError (int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RICHEDIT_CLASS ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CHILD ; 
 int WS_HSCROLL ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static BOOL
InitEditWnd(PEDIT_WND_INFO Info)
{
    HANDLE hDLL;
    HFONT hfDefault;

    hDLL = LoadLibrary(_T("RICHED20.DLL"));
    if (hDLL == NULL)
    {
        GetError(0);
        return FALSE;
    }

    Info->hEdit = CreateWindowEx(0, //WS_EX_CLIENTEDGE,
                                 RICHEDIT_CLASS,
                                 NULL,
                                 WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
                                   ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                                 0,
                                 0,
                                 100,
                                 100,
                                 Info->hSelf,
                                 NULL,
                                 hInstance,
                                 NULL);
    if(Info->hEdit == NULL)
    {
        GetError(0);

        return FALSE;
    }

    hfDefault = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(Info->hEdit,
                WM_SETFONT,
                (WPARAM)hfDefault,
                MAKELPARAM(FALSE, 0));

    return TRUE;
}