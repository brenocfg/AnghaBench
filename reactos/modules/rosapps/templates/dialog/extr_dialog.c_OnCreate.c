#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pszText; void* mask; } ;
typedef  TYPE_1__ TCITEM ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_2__ INITCOMMONCONTROLSEX ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DLGPROC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* CreateDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICC_TAB_CLASSES ; 
 int /*<<< orphan*/  IDC_TAB ; 
 int /*<<< orphan*/  IDD_PAGE1 ; 
 int /*<<< orphan*/  IDD_PAGE2 ; 
 int /*<<< orphan*/  IDD_PAGE3 ; 
 int /*<<< orphan*/  InitCommonControls () ; 
 int /*<<< orphan*/  InitCommonControlsEx (TYPE_2__*) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 scalar_t__ PageWndProc1 ; 
 scalar_t__ PageWndProc2 ; 
 scalar_t__ PageWndProc3 ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (void*,int /*<<< orphan*/ ) ; 
 void* TCIF_TEXT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TabCtrl_InsertItem (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 
 void* hPage1 ; 
 void* hPage2 ; 
 void* hPage3 ; 
 int /*<<< orphan*/  hTabWnd ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL OnCreate(HWND hWnd, LONG lData)
{
    TCHAR szTemp[256];
    TCITEM item;

    // Initialize the Windows Common Controls DLL
#ifdef __GNUC__
    InitCommonControls();
#else
    INITCOMMONCONTROLSEX ex = { sizeof(INITCOMMONCONTROLSEX), ICC_TAB_CLASSES };
    InitCommonControlsEx(&ex);
#endif

    // Create tab pages
    hTabWnd = GetDlgItem(hWnd, IDC_TAB);
    hPage1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_PAGE1), hWnd, (DLGPROC)PageWndProc1);
    hPage2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_PAGE2), hWnd, (DLGPROC)PageWndProc2);
    hPage3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_PAGE3), hWnd, (DLGPROC)PageWndProc3);

    // Insert tabs
    _tcscpy(szTemp, _T("Page One"));
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    TabCtrl_InsertItem(hTabWnd, 0, &item);
    _tcscpy(szTemp, _T("Page Two"));
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    TabCtrl_InsertItem(hTabWnd, 1, &item);
    _tcscpy(szTemp, _T("Page Three"));
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    TabCtrl_InsertItem(hTabWnd, 2, &item);

    ShowWindow(hPage1, SW_SHOW);

    return TRUE;
}