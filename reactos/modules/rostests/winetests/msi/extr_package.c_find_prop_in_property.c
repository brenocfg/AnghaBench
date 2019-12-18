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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiRecordGetStringA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  MsiViewClose (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewFetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static BOOL find_prop_in_property(MSIHANDLE hdb, LPCSTR prop, LPCSTR val, int len)
{
    MSIHANDLE hview, hrec;
    BOOL found = FALSE;
    CHAR buffer[MAX_PATH];
    DWORD sz;
    UINT r;

    r = MsiDatabaseOpenViewA(hdb, "SELECT * FROM `_Property`", &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");

    if (len < 0) len = lstrlenA(val);

    while (r == ERROR_SUCCESS && !found)
    {
        r = MsiViewFetch(hview, &hrec);
        if (r != ERROR_SUCCESS) break;

        sz = MAX_PATH;
        r = MsiRecordGetStringA(hrec, 1, buffer, &sz);
        if (r == ERROR_SUCCESS && !lstrcmpA(buffer, prop))
        {
            sz = MAX_PATH;
            r = MsiRecordGetStringA(hrec, 2, buffer, &sz);
            if (r == ERROR_SUCCESS && !memcmp(buffer, val, len) && !buffer[len])
            {
                ok(sz == len, "wrong size %u\n", sz);
                found = TRUE;
            }
        }

        MsiCloseHandle(hrec);
    }
    MsiViewClose(hview);
    MsiCloseHandle(hview);
    return found;
}