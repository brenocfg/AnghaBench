#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  hWndListView; void* hImageListLarge; void* hImageListSmall; int /*<<< orphan*/  hInst; int /*<<< orphan*/  hWnd; int /*<<< orphan*/  hWndStatusBar; } ;
struct TYPE_8__ {int mask; int iSubItem; int cx; int /*<<< orphan*/  fmt; int /*<<< orphan*/ * pszText; } ;
struct TYPE_7__ {int right; int left; scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ LVCOLUMNW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_3__ CPanel ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_LISTVIEW ; 
 int /*<<< orphan*/  IDS_CPANEL_DESCRIPTION ; 
 int /*<<< orphan*/  IDS_CPANEL_NAME ; 
 int ILC_COLOR32 ; 
 int ILC_MASK ; 
 void* ImageList_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int LISTVIEW_DEFSTYLE ; 
 int /*<<< orphan*/  LVCFMT_LEFT ; 
 int LVCF_FMT ; 
 int LVCF_SUBITEM ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int /*<<< orphan*/  LVM_SETIMAGELIST ; 
 int /*<<< orphan*/  LVSIL_NORMAL ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int LVS_ICON ; 
 int ListView_InsertColumnW (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_STRING_LEN ; 
 int /*<<< orphan*/  SM_CXICON ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WC_LISTVIEWW ; 
 int /*<<< orphan*/  WS_EX_CLIENTEDGE ; 
 int /*<<< orphan*/  shell32_hInstance ; 

__attribute__((used)) static BOOL Control_CreateListView (CPanel *panel)
{
    RECT ws, sb;
    WCHAR empty_string[] = {0};
    WCHAR buf[MAX_STRING_LEN];
    LVCOLUMNW lvc;

    /* Create list view */
    GetClientRect(panel->hWndStatusBar, &sb);
    GetClientRect(panel->hWnd, &ws);

    panel->hWndListView = CreateWindowExW(WS_EX_CLIENTEDGE, WC_LISTVIEWW,
                          empty_string, LISTVIEW_DEFSTYLE | LVS_ICON,
                          0, 0, ws.right - ws.left, ws.bottom - ws.top -
                          (sb.bottom - sb.top), panel->hWnd,
                          (HMENU) IDC_LISTVIEW, panel->hInst, NULL);

    if (!panel->hWndListView)
        return FALSE;

    /* Create image lists for list view */
    panel->hImageListSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON), ILC_COLOR32 | ILC_MASK, 1, 1);
    panel->hImageListLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
        GetSystemMetrics(SM_CYICON), ILC_COLOR32 | ILC_MASK, 1, 1);

    SendMessageW(panel->hWndListView, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)panel->hImageListSmall);
    SendMessageW(panel->hWndListView, LVM_SETIMAGELIST, LVSIL_NORMAL, (LPARAM)panel->hImageListLarge);

    /* Create columns for list view */
    lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
    lvc.pszText = buf;
    lvc.fmt = LVCFMT_LEFT;

    /* Name column */
    lvc.iSubItem = 0;
    lvc.cx = (ws.right - ws.left) / 3;
    LoadStringW(shell32_hInstance, IDS_CPANEL_NAME, buf, sizeof(buf) / sizeof(buf[0]));

    if (ListView_InsertColumnW(panel->hWndListView, 0, &lvc) == -1)
        return FALSE;

    /* Description column */
    lvc.iSubItem = 1;
    lvc.cx = ((ws.right - ws.left) / 3) * 2;
    LoadStringW(shell32_hInstance, IDS_CPANEL_DESCRIPTION, buf, sizeof(buf) /
        sizeof(buf[0]));

    if (ListView_InsertColumnW(panel->hWndListView, 1, &lvc) == -1)
        return FALSE;

    return(TRUE);
}