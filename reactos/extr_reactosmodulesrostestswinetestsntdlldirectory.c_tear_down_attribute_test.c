#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const WCHAR ;
struct TYPE_2__ {int attr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DeleteFileW (int /*<<< orphan*/  const*) ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int RemoveDirectoryW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  backslashW ; 
 int /*<<< orphan*/  dotW ; 
 int /*<<< orphan*/  dotdotW ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int test_dir_count ; 
 TYPE_1__* testfiles ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void tear_down_attribute_test(const WCHAR *testdir)
{
    int i;

    for (i = 0; i < test_dir_count; i++) {
        int ret;
        WCHAR buf[MAX_PATH];
        if (lstrcmpW(testfiles[i].name, dotW) == 0 || lstrcmpW(testfiles[i].name, dotdotW) == 0)
            continue;
        lstrcpyW( buf, testdir );
        lstrcatW( buf, backslashW );
        lstrcatW( buf, testfiles[i].name );
        if (testfiles[i].attr & FILE_ATTRIBUTE_DIRECTORY) {
            ret = RemoveDirectoryW(buf);
            ok(ret || (GetLastError() == ERROR_PATH_NOT_FOUND),
               "Failed to rmdir %s, error %d\n", wine_dbgstr_w(buf), GetLastError());
        } else {
            ret = DeleteFileW(buf);
            ok(ret || (GetLastError() == ERROR_PATH_NOT_FOUND),
               "Failed to rm %s, error %d\n", wine_dbgstr_w(buf), GetLastError());
        }
    }
    RemoveDirectoryW(testdir);
}