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

/* Variables and functions */
 int MB_DEFBUTTON3 ; 
 int MB_ICONINFORMATION ; 
 int MB_SERVICE_NOTIFICATION ; 
 int MB_YESNOCANCEL ; 
 int MessageBoxW (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void TestMsgBoxServiceNotification(void)
{
    int res;

    res = MessageBoxW(NULL, L"Hello World!", L"MB_SERVICE_NOTIFICATION",
                      MB_YESNOCANCEL | MB_DEFBUTTON3 | MB_ICONINFORMATION | /* MB_DEFAULT_DESKTOP_ONLY | */ MB_SERVICE_NOTIFICATION);
    printf("Returned value = %i\n", res);
}