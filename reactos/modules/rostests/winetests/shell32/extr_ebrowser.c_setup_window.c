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
struct TYPE_4__ {char const* lpszClassName; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSW ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DefWindowProcW ; 
 int /*<<< orphan*/  RegisterClassW (TYPE_1__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void setup_window(void)
{
    WNDCLASSW wc;
    static const WCHAR ebtestW[] = {'e','b','t','e','s','t',0};

    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.lpfnWndProc      = DefWindowProcW;
    wc.lpszClassName    = ebtestW;
    RegisterClassW(&wc);
    hwnd = CreateWindowExW(0, ebtestW, NULL, 0,
                           0, 0, 500, 500,
                           NULL, 0, 0, NULL);
    ok(hwnd != NULL, "Failed to create window for tests.\n");
}