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
typedef  int /*<<< orphan*/  wcA ;
typedef  int /*<<< orphan*/  WNDPROC ;
struct TYPE_4__ {int /*<<< orphan*/  hInstance; int /*<<< orphan*/  lpszClassName; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void create_dde_window(HWND *hwnd, LPCSTR name, WNDPROC wndproc)
{
    WNDCLASSA wcA;
    ATOM aclass;

    memset(&wcA, 0, sizeof(wcA));
    wcA.lpfnWndProc = wndproc;
    wcA.lpszClassName = name;
    wcA.hInstance = GetModuleHandleA(0);
    aclass = RegisterClassA(&wcA);
    ok (aclass, "RegisterClass failed\n");

    *hwnd = CreateWindowExA(0, name, NULL, WS_POPUP,
                            500, 500, CW_USEDEFAULT, CW_USEDEFAULT,
                            GetDesktopWindow(), 0, GetModuleHandleA(0), NULL);
    ok(*hwnd != NULL, "CreateWindowExA failed\n");
}