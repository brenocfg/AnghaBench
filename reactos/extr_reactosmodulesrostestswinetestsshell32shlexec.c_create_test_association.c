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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_SET_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  create_test_class (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static BOOL create_test_association(const char* extension)
{
    HKEY hkey;
    char class[MAX_PATH];
    LONG rc;

    sprintf(class, "shlexec%s", extension);
    rc=RegCreateKeyExA(HKEY_CLASSES_ROOT, extension, 0, NULL, 0, KEY_SET_VALUE,
                       NULL, &hkey, NULL);
    ok(rc == ERROR_SUCCESS || rc == ERROR_ACCESS_DENIED,
       "could not create association %s (rc=%d)\n", class, rc);
    if (rc != ERROR_SUCCESS)
        return FALSE;

    rc=RegSetValueExA(hkey, NULL, 0, REG_SZ, (LPBYTE) class, strlen(class)+1);
    ok(rc==ERROR_SUCCESS, "RegSetValueEx '%s' failed, expected ERROR_SUCCESS, got %d\n", class, rc);
    CloseHandle(hkey);

    return create_test_class(class, FALSE);
}