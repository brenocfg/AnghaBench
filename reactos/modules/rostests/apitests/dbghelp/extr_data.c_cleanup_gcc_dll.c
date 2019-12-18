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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char const*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 char* tmpdir () ; 

void cleanup_gcc_dll()
{
    char szFile[MAX_PATH];
    BOOL ret;
    const char* dir = tmpdir();

    sprintf(szFile, "%s\\uffs.dll", dir);
    ret = DeleteFileA(szFile);
    ok(ret, "DeleteFileA failed(%d)\n", GetLastError());
    ret = RemoveDirectoryA(dir);
    ok(ret, "RemoveDirectoryA failed(%d)\n", GetLastError());
}