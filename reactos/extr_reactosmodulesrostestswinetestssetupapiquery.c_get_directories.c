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
 char* CURR_DIR ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 char* WIN_DIR ; 
 int lstrlenA (char*) ; 

__attribute__((used)) static void get_directories(void)
{
    int len;

    GetCurrentDirectoryA(MAX_PATH, CURR_DIR);
    len = lstrlenA(CURR_DIR);

    if(len && (CURR_DIR[len-1] == '\\'))
        CURR_DIR[len-1] = 0;

    GetWindowsDirectoryA(WIN_DIR, MAX_PATH);
    len = lstrlenA(WIN_DIR);

    if (len && (WIN_DIR[len-1] == '\\'))
        WIN_DIR[len-1] = 0;
}