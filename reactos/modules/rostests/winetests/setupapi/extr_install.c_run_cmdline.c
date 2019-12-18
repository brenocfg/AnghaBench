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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  InstallHinfSectionW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*,int,char*) ; 

__attribute__((used)) static void run_cmdline(LPCSTR section, int mode, LPCSTR path)
{
    CHAR cmdline[MAX_PATH * 2];
    WCHAR cmdlinew[MAX_PATH * 2];

    sprintf(cmdline, "%s %d %s", section, mode, path);
    MultiByteToWideChar(CP_ACP, 0, cmdline, -1, cmdlinew, MAX_PATH*2);
    InstallHinfSectionW(NULL, NULL, cmdlinew, 0);
}