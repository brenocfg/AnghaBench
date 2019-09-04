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
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void delete_win_ini(LPCSTR file)
{
    CHAR path[MAX_PATH];

    GetWindowsDirectoryA(path, MAX_PATH);
    lstrcatA(path, "\\");
    lstrcatA(path, file);

    DeleteFileA(path);
}