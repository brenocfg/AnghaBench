#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {TYPE_1__* applet; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ CPlItem ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShellExecuteW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfW (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Control_StartApplet(HWND hWnd, CPlItem *item)
{
    WCHAR verbOpen[] = {'c','p','l','o','p','e','n',0};
    WCHAR format[] = {'@','%','d',0};
    WCHAR param[MAX_PATH];

    /* execute the applet if item is valid */
    if (item)
    {
        wsprintfW(param, format, item->id);
        ShellExecuteW(hWnd, verbOpen, item->applet->cmd, param, NULL, SW_SHOW);
    }
}