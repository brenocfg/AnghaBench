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
struct TYPE_3__ {char* lpszClassName; int /*<<< orphan*/ * lpszMenuName; int /*<<< orphan*/ * hbrBackground; int /*<<< orphan*/  hCursor; scalar_t__ hIcon; int /*<<< orphan*/  hInstance; scalar_t__ cbWndExtra; scalar_t__ cbClsExtra; int /*<<< orphan*/  lpfnWndProc; scalar_t__ style; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefWindowProcA ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_WINDOW_HANDLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int GetWindowLongA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_ARROW ; 
 int IsWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadCursorA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  UnregisterClassA (char*,int /*<<< orphan*/ ) ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pSHSetWindowBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void test_SHSetWindowBits(void)
{
    HWND hwnd;
    DWORD style, styleold;
    WNDCLASSA clsA;

    clsA.style = 0;
    clsA.lpfnWndProc = DefWindowProcA;
    clsA.cbClsExtra = 0;
    clsA.cbWndExtra = 0;
    clsA.hInstance = GetModuleHandleA(NULL);
    clsA.hIcon = 0;
    clsA.hCursor = LoadCursorA(0, (LPSTR)IDC_ARROW);
    clsA.hbrBackground = NULL;
    clsA.lpszMenuName = NULL;
    clsA.lpszClassName = "Shlwapi test class";
    RegisterClassA(&clsA);

    hwnd = CreateWindowA("Shlwapi test class", "Test", WS_VISIBLE, 0, 0, 100, 100,
                          NULL, NULL, GetModuleHandleA(NULL), 0);
    ok(IsWindow(hwnd), "failed to create window\n");

    /* null window */
    SetLastError(0xdeadbeef);
    style = pSHSetWindowBits(NULL, GWL_STYLE, 0, 0);
    ok(style == 0, "expected 0 retval, got %d\n", style);
    ok(GetLastError() == ERROR_INVALID_WINDOW_HANDLE,
        "expected ERROR_INVALID_WINDOW_HANDLE, got %d\n", GetLastError());

    /* zero mask, zero flags */
    styleold = GetWindowLongA(hwnd, GWL_STYLE);
    style = pSHSetWindowBits(hwnd, GWL_STYLE, 0, 0);
    ok(styleold == style, "expected old style\n");
    ok(styleold == GetWindowLongA(hwnd, GWL_STYLE), "expected to keep old style\n");

    /* test mask */
    styleold = GetWindowLongA(hwnd, GWL_STYLE);
    ok(styleold & WS_VISIBLE, "expected WS_VISIBLE\n");
    style = pSHSetWindowBits(hwnd, GWL_STYLE, WS_VISIBLE, 0);

    ok(style == styleold, "expected previous style, got %x\n", style);
    ok((GetWindowLongA(hwnd, GWL_STYLE) & WS_VISIBLE) == 0, "expected updated style\n");

    /* test mask, unset style bit used */
    styleold = GetWindowLongA(hwnd, GWL_STYLE);
    style = pSHSetWindowBits(hwnd, GWL_STYLE, WS_VISIBLE, 0);
    ok(style == styleold, "expected previous style, got %x\n", style);
    ok(styleold == GetWindowLongA(hwnd, GWL_STYLE), "expected to keep old style\n");

    /* set back with flags */
    styleold = GetWindowLongA(hwnd, GWL_STYLE);
    style = pSHSetWindowBits(hwnd, GWL_STYLE, WS_VISIBLE, WS_VISIBLE);
    ok(style == styleold, "expected previous style, got %x\n", style);
    ok(GetWindowLongA(hwnd, GWL_STYLE) & WS_VISIBLE, "expected updated style\n");

    /* reset and try to set without a mask */
    pSHSetWindowBits(hwnd, GWL_STYLE, WS_VISIBLE, 0);
    ok((GetWindowLongA(hwnd, GWL_STYLE) & WS_VISIBLE) == 0, "expected updated style\n");
    styleold = GetWindowLongA(hwnd, GWL_STYLE);
    style = pSHSetWindowBits(hwnd, GWL_STYLE, 0, WS_VISIBLE);
    ok(style == styleold, "expected previous style, got %x\n", style);
    ok((GetWindowLongA(hwnd, GWL_STYLE) & WS_VISIBLE) == 0, "expected updated style\n");

    DestroyWindow(hwnd);

    UnregisterClassA("Shlwapi test class", GetModuleHandleA(NULL));
}