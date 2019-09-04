#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cbSize; scalar_t__ hIcon; char* lpszClassName; int /*<<< orphan*/ * hIconSm; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSEXW ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  ICONINFO ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/  ClassTest_WndProc ; 
 int /*<<< orphan*/ * CopyImage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateWindowExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCLP_HICON ; 
 int /*<<< orphan*/  GCLP_HICONSM ; 
 int GetClassInfoExW (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 scalar_t__ GetClassLongPtrW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetIconInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICON_BIG ; 
 int /*<<< orphan*/  ICON_SMALL ; 
 int /*<<< orphan*/  ICON_SMALL2 ; 
 scalar_t__ IDI_APPLICATION ; 
 scalar_t__ IDI_QUESTION ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 scalar_t__ LoadIconW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RegisterClassExW (TYPE_1__*) ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClassLongPtrW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterClassW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETICON ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_icons(void)
{
    WNDCLASSEXW wcex, ret_wcex;
    WCHAR cls_name[] = {'I','c','o','n','T','e','s','t','C','l','a','s','s',0};
    HWND hwnd;
    HINSTANCE hinst = GetModuleHandleW(0);
    HICON hsmicon, hsmallnew;
    ICONINFO icinf;

    memset(&wcex, 0, sizeof wcex);
    wcex.cbSize        = sizeof wcex;
    wcex.lpfnWndProc   = ClassTest_WndProc;
    wcex.hIcon         = LoadIconW(0, (LPCWSTR)IDI_APPLICATION);
    wcex.hInstance     = hinst;
    wcex.lpszClassName = cls_name;
    ok(RegisterClassExW(&wcex), "RegisterClassExW returned 0\n");
    hwnd = CreateWindowExW(0, cls_name, NULL, WS_OVERLAPPEDWINDOW,
                        0, 0, 0, 0, NULL, NULL, hinst, 0);
    ok(hwnd != NULL, "Window was not created\n");

    ok(GetClassInfoExW(hinst, cls_name, &ret_wcex), "Class info was not retrieved\n");
    ok(wcex.hIcon == ret_wcex.hIcon, "Icons don't match\n");
    ok(ret_wcex.hIconSm != NULL, "hIconSm should be non-zero handle\n");

    hsmicon = (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
    ok(hsmicon != NULL, "GetClassLong should return non-zero handle\n");

    ok(SendMessageA(hwnd, WM_GETICON, ICON_BIG, 0) == 0,
                    "WM_GETICON with ICON_BIG should not return the class icon\n");
    ok(SendMessageA(hwnd, WM_GETICON, ICON_SMALL, 0) == 0,
                    "WM_GETICON with ICON_SMALL should not return the class icon\n");
    ok(SendMessageA(hwnd, WM_GETICON, ICON_SMALL2, 0) == 0,
                    "WM_GETICON with ICON_SMALL2 should not return the class icon\n");

    hsmallnew = CopyImage(wcex.hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
                                                GetSystemMetrics(SM_CYSMICON), 0);
    ok(!SetClassLongPtrW(hwnd, GCLP_HICONSM, (LONG_PTR)hsmallnew),
                    "Previous hIconSm should be zero\n");
    ok(hsmallnew == (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM),
                    "Should return explicitly assigned small icon\n");
    ok(!GetIconInfo(hsmicon, &icinf), "Previous small icon should be destroyed\n");

    SetClassLongPtrW(hwnd, GCLP_HICONSM, 0);
    hsmicon = (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
    ok( hsmicon != NULL, "GetClassLong should return non-zero handle\n");

    SetClassLongPtrW(hwnd, GCLP_HICON, 0);
    ok(!GetClassLongPtrW(hwnd, GCLP_HICONSM), "GetClassLong should return zero handle\n");

    SetClassLongPtrW(hwnd, GCLP_HICON, (LONG_PTR)LoadIconW(NULL, (LPCWSTR)IDI_QUESTION));
    hsmicon = (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
    ok(hsmicon != NULL, "GetClassLong should return non-zero handle\n");
    UnregisterClassW(cls_name, hinst);
    ok(GetIconInfo(hsmicon, &icinf), "Icon should NOT be destroyed\n");

    DestroyIcon(hsmallnew);
    DestroyWindow(hwnd);
}