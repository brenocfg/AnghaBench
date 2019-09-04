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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  REG_NOTIFY_CHANGE_NAME ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegNotifyChangeKeyValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_RegNotifyChangeKeyValue(void)
{
    HKEY key, subkey;
    HANDLE event;
    DWORD dwret;
    LONG ret;

    event = CreateEventW(NULL, FALSE, TRUE, NULL);
    ok(event != NULL, "CreateEvent failed, error %u\n", GetLastError());
    ret = RegCreateKeyA(hkey_main, "TestKey", &key);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);

    ret = RegNotifyChangeKeyValue(key, TRUE, REG_NOTIFY_CHANGE_NAME, event, TRUE);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    dwret = WaitForSingleObject(event, 0);
    ok(dwret == WAIT_TIMEOUT, "expected WAIT_TIMEOUT, got %u\n", dwret);

    ret = RegCreateKeyA(key, "SubKey", &subkey);
    ok(ret == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", ret);
    dwret = WaitForSingleObject(event, 0);
    ok(dwret == WAIT_OBJECT_0, "expected WAIT_OBJECT_0, got %u\n", dwret);

    RegDeleteKeyA(key, "");
    RegCloseKey(key);
    CloseHandle(event);
}