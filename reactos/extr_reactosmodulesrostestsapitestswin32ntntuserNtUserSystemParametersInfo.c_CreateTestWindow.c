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
struct TYPE_3__ {char* lpszClassName; int /*<<< orphan*/ * lpszMenuName; int /*<<< orphan*/ * hbrBackground; int /*<<< orphan*/ * hCursor; int /*<<< orphan*/ * hIcon; int /*<<< orphan*/  hInstance; scalar_t__ cbWndExtra; scalar_t__ cbClsExtra; int /*<<< orphan*/  lpfnWndProc; scalar_t__ style; } ;
typedef  TYPE_1__ WNDCLASSA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefWindowProcA ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterClassA (TYPE_1__*) ; 
 int /*<<< orphan*/  WS_VISIBLE ; 

HWND
CreateTestWindow()
{
    HINSTANCE hinst = GetModuleHandle(NULL);
    WNDCLASSA wc;

    wc.style = 0;
    wc.lpfnWndProc = DefWindowProcA;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinst;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "testclass";

    RegisterClassA(&wc);
    return CreateWindowA("testclass",
                         "testwnd",
                         WS_VISIBLE,
                         0,
                         0,
                         50,
                         30,
                         NULL,
                         NULL,
                         hinst,
                         0);
}