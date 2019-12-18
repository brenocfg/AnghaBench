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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int KEY_CREATE_SUB_KEY ; 
 int KEY_SET_VALUE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCreateKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 

__attribute__((used)) static BOOL create_test_class(const char* class, BOOL protocol)
{
    HKEY hkey, hkey_shell;
    LONG rc;

    rc = RegCreateKeyExA(HKEY_CLASSES_ROOT, class, 0, NULL, 0,
                         KEY_CREATE_SUB_KEY | KEY_SET_VALUE, NULL,
                         &hkey, NULL);
    ok(rc == ERROR_SUCCESS || rc == ERROR_ACCESS_DENIED,
       "could not create class %s (rc=%d)\n", class, rc);
    if (rc != ERROR_SUCCESS)
        return FALSE;

    if (protocol)
    {
        rc = RegSetValueExA(hkey, "URL Protocol", 0, REG_SZ, (LPBYTE)"", 1);
        ok(rc == ERROR_SUCCESS, "RegSetValueEx '%s' failed, expected ERROR_SUCCESS, got %d\n", class, rc);
    }

    rc = RegCreateKeyExA(hkey, "shell", 0, NULL, 0,
                         KEY_CREATE_SUB_KEY, NULL, &hkey_shell, NULL);
    ok(rc == ERROR_SUCCESS, "RegCreateKeyEx 'shell' failed, expected ERROR_SUCCESS, got %d\n", rc);

    CloseHandle(hkey);
    CloseHandle(hkey_shell);
    return TRUE;
}