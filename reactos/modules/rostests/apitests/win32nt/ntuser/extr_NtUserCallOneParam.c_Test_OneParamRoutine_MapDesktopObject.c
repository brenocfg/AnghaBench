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
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HMENU ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CreateMenu () ; 
 int /*<<< orphan*/  DestroyMenu (scalar_t__) ; 
 scalar_t__ GetDesktopWindow () ; 
 int NtUserCallOneParam (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 
 int /*<<< orphan*/  _ONEPARAM_ROUTINE_MAPDEKTOPOBJECT ; 

void
Test_OneParamRoutine_MapDesktopObject(void) /* 0x30 */
{
    DWORD pObject;
    HWND hWnd;
    HMENU hMenu;

    hWnd = GetDesktopWindow();
    pObject = NtUserCallOneParam((DWORD)hWnd, _ONEPARAM_ROUTINE_MAPDEKTOPOBJECT);
    TEST(pObject > 0);
    TEST(pObject < 0x80000000);

    hMenu = CreateMenu();
    pObject = NtUserCallOneParam((DWORD)hMenu, _ONEPARAM_ROUTINE_MAPDEKTOPOBJECT);
    DestroyMenu(hMenu);
    TEST(pObject > 0);
    TEST(pObject < 0x80000000);

}