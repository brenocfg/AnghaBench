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
typedef  int /*<<< orphan*/  toolbarBtns ;
struct TYPE_9__ {int member_0; int member_1; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ WNDCLASSEX ;
struct TYPE_10__ {int member_0; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ WNDCLASS ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_12__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_11__ {int member_0; int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_3__ TBBUTTON ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_4__ INITCOMMONCONTROLSEX ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  scalar_t__ ATOM ;

/* Variables and functions */
 int CS_CLASSDC ; 
 int CS_DBLCLKS ; 
 int CS_HREDRAW ; 
 int CS_VREDRAW ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ChildWndProc ; 
 int /*<<< orphan*/  CreateFont (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateStatusWindow (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateToolbarEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CreateWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FrameWndProc ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICC_BAR_CLASSES ; 
 int /*<<< orphan*/  IDB_TOOLBAR ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  IDC_MDI_APP ; 
 int /*<<< orphan*/  IDC_STATUSBAR ; 
 int /*<<< orphan*/  IDC_TOOLBAR ; 
 int /*<<< orphan*/  IDI_MDI_APP ; 
 int /*<<< orphan*/  ID_OPTIONS_MENU ; 
 int /*<<< orphan*/  ID_OPTIONS_STATUSBAR ; 
 int /*<<< orphan*/  ID_OPTIONS_TOOLBAR ; 
 int ID_WINDOW_CASCADE ; 
 int ID_WINDOW_NEW_WINDOW ; 
 int ID_WINDOW_TILE_HORZ ; 
 int ID_WINDOW_TILE_VERT ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 scalar_t__ InitCommonControlsEx (TYPE_4__*) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  LR_SHARED ; 
 int /*<<< orphan*/  LoadAccelerators (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadIcon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int MF_GRAYED ; 
 int /*<<< orphan*/  MulDiv (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RegisterClass (TYPE_2__*) ; 
 scalar_t__ RegisterClassEx (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SBT_NOBORDERS ; 
 int /*<<< orphan*/  SB_SETPARTS ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TBSTYLE_BUTTON ; 
 int /*<<< orphan*/  TBSTYLE_SEP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateStatusBar () ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_CLIPSIBLINGS ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  hAccel ; 
 int /*<<< orphan*/  hFont ; 
 int /*<<< orphan*/  hFrameWnd ; 
 int /*<<< orphan*/  hMenuFrame ; 
 int /*<<< orphan*/  hStatusBar ; 
 int /*<<< orphan*/  hToolBar ; 
 int /*<<< orphan*/  szChildClass ; 
 int /*<<< orphan*/  szFrameClass ; 
 int /*<<< orphan*/  szTitle ; 

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wcFrame = {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW/*style*/,
        FrameWndProc,
        0/*cbClsExtra*/,
        0/*cbWndExtra*/,
        hInstance,
        LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI_APP)),
        LoadCursor(0, IDC_ARROW),
        0/*hbrBackground*/,
        0/*lpszMenuName*/,
        szFrameClass,
        (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_MDI_APP), IMAGE_ICON,
            GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_SHARED)
    };
    ATOM hFrameWndClass = RegisterClassEx(&wcFrame); // register frame window class
#if 0
    WNDCLASS wcChild = {
        CS_CLASSDC|CS_DBLCLKS|CS_VREDRAW,
        ChildWndProc,
        0/*cbClsExtra*/,
        0/*cbWndExtra*/,
        hInstance,
        0/*hIcon*/,
        LoadCursor(0, IDC_ARROW),
        0/*hbrBackground*/,
        0/*lpszMenuName*/,
        szChildClass
    };
    ATOM hChildWndClass = RegisterClass(&wcChild); // register child windows class
#else
    // WNDCLASSEX wcChild = {
    //     sizeof(WNDCLASSEX),
    //     CS_HREDRAW | CS_VREDRAW/*style*/,
    //     ChildWndProc,
    //     0/*cbClsExtra*/,
    //     sizeof(HANDLE)/*cbWndExtra*/,
    //     hInstance,
    //     LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI_APP)),
    //     LoadCursor(0, IDC_ARROW),
    //     0/*hbrBackground*/,
    //     0/*lpszMenuName*/,
    //     szChildClass,
    //     (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDC_MDI_APP), IMAGE_ICON,
    //         GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_SHARED)
    // };
    // ATOM hChildWndClass = RegisterClassEx(&wcChild); // register child windows class
#endif

    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_MDI_APP));
    HMENU hMenuOptions = GetSubMenu(hMenu, ID_OPTIONS_MENU);
    // HMENU hChildMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_MDI_APP_CHILD));

    INITCOMMONCONTROLSEX icc = {
        sizeof(INITCOMMONCONTROLSEX),
        ICC_BAR_CLASSES
    };

    HDC hdc = GetDC(0);

    hMenuFrame = hMenu;
//  hMenuView = GetSubMenu(hMenuFrame, ID_VIEW_MENU);
    hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MDI_APP));
    hFont = CreateFont(-MulDiv(8,GetDeviceCaps(hdc,LOGPIXELSY),72), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("MS Sans Serif"));
    ReleaseDC(0, hdc);

    hFrameWnd = CreateWindowEx(0, (LPCTSTR)(ULONG_PTR)hFrameWndClass, szTitle,
//  hFrameWnd = CreateWindow(szFrameClass, szTitle,
                    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                    NULL/*hWndParent*/, hMenuFrame, hInstance, NULL/*lpParam*/);
    if (!hFrameWnd) {
        return FALSE;
    }

    if (InitCommonControlsEx(&icc))
    {
        int nParts[3];
        TBBUTTON toolbarBtns[] = {
            {0, 0, 0, TBSTYLE_SEP},
            {0, ID_WINDOW_NEW_WINDOW, TBSTATE_ENABLED, TBSTYLE_BUTTON},
            {1, ID_WINDOW_CASCADE, TBSTATE_ENABLED, TBSTYLE_BUTTON},
            {2, ID_WINDOW_TILE_HORZ, TBSTATE_ENABLED, TBSTYLE_BUTTON},
            {3, ID_WINDOW_TILE_VERT, TBSTATE_ENABLED, TBSTYLE_BUTTON},
            {4, 2/*TODO: ID_...*/, TBSTATE_ENABLED, TBSTYLE_BUTTON},
            {5, 2/*TODO: ID_...*/, TBSTATE_ENABLED, TBSTYLE_BUTTON},
        };

        hToolBar = CreateToolbarEx(hFrameWnd, WS_CHILD|WS_VISIBLE,
            IDC_TOOLBAR, 2, hInstance, IDB_TOOLBAR, toolbarBtns,
            sizeof(toolbarBtns)/sizeof(TBBUTTON), 16, 15, 16, 15, sizeof(TBBUTTON));
        CheckMenuItem(hMenuOptions, ID_OPTIONS_TOOLBAR, MF_BYCOMMAND|MF_CHECKED);

        // Create the status bar
        hStatusBar = CreateStatusWindow(WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|SBT_NOBORDERS,
                                        "", hFrameWnd, IDC_STATUSBAR);
        if (!hStatusBar)
            return FALSE;
        CheckMenuItem(hMenuOptions, ID_OPTIONS_STATUSBAR, MF_BYCOMMAND|MF_CHECKED);

        // Create the status bar panes
        nParts[0] = 100;
        nParts[1] = 210;
        nParts[2] = 400;
        SendMessage(hStatusBar, SB_SETPARTS, 3, (LPARAM)nParts);
    } else {
        CheckMenuItem(hMenuOptions, ID_OPTIONS_TOOLBAR, MF_BYCOMMAND|MF_GRAYED);
        CheckMenuItem(hMenuOptions, ID_OPTIONS_STATUSBAR, MF_BYCOMMAND|MF_GRAYED);
	}

    ShowWindow(hFrameWnd, nCmdShow);
    UpdateWindow(hFrameWnd);
    UpdateStatusBar();
    return TRUE;
}