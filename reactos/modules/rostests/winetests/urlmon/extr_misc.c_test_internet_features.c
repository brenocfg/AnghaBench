#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int CreateProcessA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MAX_PATH ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pCoInternetIsFeatureEnabled ; 
 int /*<<< orphan*/  pCoInternetSetFeatureEnabled ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  szFeatureControlKey ; 
 int /*<<< orphan*/  test_CoInternetIsFeatureEnabled () ; 
 int /*<<< orphan*/  test_CoInternetSetFeatureEnabled () ; 
 int /*<<< orphan*/  test_internet_features_registry () ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  winetest_get_mainargs (char***) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_internet_features(void) {
    HKEY key;
    DWORD res;

    if(!pCoInternetIsFeatureEnabled || !pCoInternetSetFeatureEnabled) {
        win_skip("Skipping internet feature tests, IE is too old\n");
        return;
    }

    /* IE10 takes FeatureControl key into account only if it's available upon process start. */
    res = RegOpenKeyA(HKEY_CURRENT_USER, szFeatureControlKey, &key);
    if(res != ERROR_SUCCESS) {
        PROCESS_INFORMATION pi;
        STARTUPINFOA si = { 0 };
        char cmdline[MAX_PATH];
        char **argv;
        BOOL ret;

        res = RegCreateKeyA(HKEY_CURRENT_USER, szFeatureControlKey, &key);
        ok(res == ERROR_SUCCESS, "RegCreateKey failed: %d\n", res);

        trace("Running features tests in a separated process.\n");

        winetest_get_mainargs( &argv );
        sprintf(cmdline, "\"%s\" %s internet_features", argv[0], argv[1]);
        ret = CreateProcessA(argv[0], cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        ok(ret, "Could not create process: %u\n", GetLastError());
        winetest_wait_child_process( pi.hProcess );
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

        RegDeleteKeyA(HKEY_CURRENT_USER, szFeatureControlKey);
        return;
    }

    test_internet_features_registry();
    test_CoInternetIsFeatureEnabled();
    test_CoInternetSetFeatureEnabled();
}