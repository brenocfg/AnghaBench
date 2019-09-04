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
typedef  int /*<<< orphan*/  wcex ;
struct TYPE_4__ {int cbSize; int style; } ;
typedef  TYPE_1__ WNDCLASSEXW ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AtlAxWinInit () ; 
 int CS_DBLCLKS ; 
 int CS_GLOBALCLASS ; 
 int /*<<< orphan*/  GetClassInfoExW (int /*<<< orphan*/ ,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_ax_win(void)
{
    BOOL ret;
    WNDCLASSEXW wcex;
    static const WCHAR AtlAxWin80[] = {'A','t','l','A','x','W','i','n','8','0',0};
    static const WCHAR AtlAxWinLic80[] = {'A','t','l','A','x','W','i','n','L','i','c','8','0',0};
    static HMODULE hinstance = 0;

    ret = AtlAxWinInit();
    ok(ret, "AtlAxWinInit failed\n");

    hinstance = GetModuleHandleA(NULL);

    memset(&wcex, 0, sizeof(wcex));
    wcex.cbSize = sizeof(wcex);
    ret = GetClassInfoExW(hinstance, AtlAxWin80, &wcex);
    ok(ret, "AtlAxWin80 has not registered\n");
    ok(wcex.style == (CS_GLOBALCLASS | CS_DBLCLKS), "wcex.style %08x\n", wcex.style);

    memset(&wcex, 0, sizeof(wcex));
    wcex.cbSize = sizeof(wcex);
    ret = GetClassInfoExW(hinstance, AtlAxWinLic80, &wcex);
    ok(ret, "AtlAxWinLic80 has not registered\n");
    ok(wcex.style == (CS_GLOBALCLASS | CS_DBLCLKS), "wcex.style %08x\n", wcex.style);
}