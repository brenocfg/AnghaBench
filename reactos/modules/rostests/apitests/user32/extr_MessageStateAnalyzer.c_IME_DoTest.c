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
typedef  int /*<<< orphan*/  wc ;
struct TYPE_4__ {int style; char const* lpszClassName; scalar_t__ hbrBackground; int /*<<< orphan*/  hCursor; int /*<<< orphan*/  hIcon; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ COLOR_3DFACE ; 
 int CS_DBLCLKS ; 
 int CS_HREDRAW ; 
 int CS_VREDRAW ; 
 int /*<<< orphan*/  CreateWindowA (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DoFinish () ; 
 int /*<<< orphan*/  DoInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIGHT ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  IDI_APPLICATION ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnregisterClassA (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIDTH ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  WindowProc ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_IMEStages ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void IME_DoTest(void)
{
    WNDCLASSA wc;
    HWND hwnd;
    MSG msg;
    static const char s_szName[] = "MessageStateAnalyzerIME";

    trace("IME_DoTest\n");
    DoInitialize(s_IMEStages, ARRAYSIZE(s_IMEStages));

    /* register window class */
    ZeroMemory(&wc, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandleA(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
    wc.lpszClassName = s_szName;
    if (!RegisterClassA(&wc))
    {
        skip("RegisterClassW failed.\n");
        return;
    }

    /* create a window */
    hwnd = CreateWindowA(s_szName, s_szName, WS_OVERLAPPEDWINDOW,
                         0, 0, WIDTH, HEIGHT, NULL, NULL,
                         GetModuleHandleW(NULL), NULL);
    if (!hwnd)
    {
        skip("CreateWindowW failed.\n");
        return;
    }

    /* message loop */
    while (GetMessageA(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    ok_int(UnregisterClassA(s_szName, GetModuleHandleA(NULL)), TRUE);

    DoFinish();
}