#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startup ;
struct TYPE_7__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_6__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CREATE_DEFAULT_ERROR_MODE ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int NORMAL_PRIORITY_CLASS ; 
 int /*<<< orphan*/  TRUE ; 
 int _mkdir (char*) ; 
 int /*<<< orphan*/  _rmdir (char*) ; 
 int /*<<< orphan*/  _unlink (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test___getmainargs_parent(char *name)
{
    char cmdline[3*MAX_PATH];
    char tmppath[MAX_PATH], filepath[MAX_PATH];
    STARTUPINFOA startup;
    PROCESS_INFORMATION proc;
    FILE *f;
    int ret;

    ok(GetTempPathA(MAX_PATH, tmppath) != 0, "GetTempPath failed\n");
    sprintf(cmdline, "%s data %s*\\* %swine_test/*", name, tmppath, tmppath);

    sprintf(filepath, "%swine_test", tmppath);
    ret = _mkdir(filepath);
    ok(!ret, "_mkdir failed: %d\n", errno);
    sprintf(filepath, "%swine_test\\a", tmppath);
    f = fopen(filepath, "w");
    ok(f != NULL, "fopen(%s) failed: %d\n", filepath, errno);
    fclose(f);
    sprintf(filepath, "%swine_test\\test", tmppath);
    f = fopen(filepath, "w");
    ok(f != NULL, "fopen(%s) failed: %d\n", filepath, errno);
    fclose(f);

    memset(&startup, 0, sizeof(startup));
    startup.cb = sizeof(startup);
    CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE|NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &proc);
    winetest_wait_child_process(proc.hProcess);

    _unlink(filepath);
    sprintf(filepath, "%swine_test\\a", tmppath);
    _unlink(filepath);
    sprintf(filepath, "%swine_test", tmppath);
    _rmdir(filepath);
}