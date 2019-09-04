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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CreateDirectoryW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  backslashW ; 
 int /*<<< orphan*/  dotW ; 
 int /*<<< orphan*/  dotdotW ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int test_dir_count ; 
 TYPE_1__* testfiles ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void set_up_attribute_test(const WCHAR *testdir)
{
    int i;
    BOOL ret;

    ret = CreateDirectoryW(testdir, NULL);
    ok(ret, "couldn't create dir %s, error %d\n", wine_dbgstr_w(testdir), GetLastError());

    for (i=0; i < test_dir_count; i++) {
        WCHAR buf[MAX_PATH];

        if (lstrcmpW(testfiles[i].name, dotW) == 0 || lstrcmpW(testfiles[i].name, dotdotW) == 0)
            continue;
        lstrcpyW( buf, testdir );
        lstrcatW( buf, backslashW );
        lstrcatW( buf, testfiles[i].name );
        if (testfiles[i].attr & FILE_ATTRIBUTE_DIRECTORY) {
            ret = CreateDirectoryW(buf, NULL);
            ok(ret, "couldn't create dir %s, error %d\n", wine_dbgstr_w(buf), GetLastError());
        } else {
            HANDLE h = CreateFileW(buf,
                                   GENERIC_READ|GENERIC_WRITE,
                                   0, NULL, CREATE_ALWAYS,
                                   testfiles[i].attr, 0);
            ok( h != INVALID_HANDLE_VALUE, "failed to create temp file %s\n", wine_dbgstr_w(buf) );
            CloseHandle(h);
        }
    }
}