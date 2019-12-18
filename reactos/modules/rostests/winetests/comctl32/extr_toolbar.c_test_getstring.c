#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  strW ;
typedef  int /*<<< orphan*/  str ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKEWPARAM (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_ADDSTRINGA ; 
 int /*<<< orphan*/  TB_GETSTRINGA ; 
 int /*<<< orphan*/  TB_GETSTRINGW ; 
 int /*<<< orphan*/  TOOLBARCLASSNAMEA ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  expect (int,scalar_t__) ; 
 int /*<<< orphan*/  hMainWnd ; 
 scalar_t__ lstrcmpA (char const*,char*) ; 
 scalar_t__ lstrcmpW (char const*,char*) ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_getstring(void)
{
    HWND hToolbar = NULL;
    char str[10];
    WCHAR strW[10];
    static const char answer[] = "STR";
    static const WCHAR answerW[] = { 'S','T','R',0 };
    INT r;

    hToolbar = CreateWindowExA(0, TOOLBARCLASSNAMEA, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMainWnd, (HMENU)5, GetModuleHandleA(NULL), NULL);
    ok(hToolbar != NULL, "Toolbar creation problem\n");

    r = SendMessageA(hToolbar, TB_GETSTRINGA, MAKEWPARAM(0, 0), 0);
    if (r == 0)
    {
        win_skip("TB_GETSTRINGA and TB_GETSTRINGW need 5.80\n");
        DestroyWindow(hToolbar);
        return;
    }
    expect(-1, r);
    r = SendMessageW(hToolbar, TB_GETSTRINGW, MAKEWPARAM(0, 0), 0);
    expect(-1, r);
    r = SendMessageA(hToolbar, TB_ADDSTRINGA, 0, (LPARAM)answer);
    expect(0, r);
    r = SendMessageA(hToolbar, TB_GETSTRINGA, MAKEWPARAM(0, 0), 0);
    expect(lstrlenA(answer), r);
    r = SendMessageW(hToolbar, TB_GETSTRINGW, MAKEWPARAM(0, 0), 0);
    expect(lstrlenA(answer), r);
    r = SendMessageA(hToolbar, TB_GETSTRINGA, MAKEWPARAM(sizeof(str), 0), (LPARAM)str);
    expect(lstrlenA(answer), r);
    expect(0, lstrcmpA(answer, str));
    r = SendMessageW(hToolbar, TB_GETSTRINGW, MAKEWPARAM(sizeof(strW), 0), (LPARAM)strW);
    expect(lstrlenA(answer), r);
    expect(0, lstrcmpW(answerW, strW));

    DestroyWindow(hToolbar);
}