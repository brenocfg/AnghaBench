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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
LONG
DeleteSubKey(HKEY hKey, LPWSTR Root, LPWSTR SubKey)
{
    HKEY RootKey;
    LONG ErrorCode;

    ErrorCode = RegOpenKeyExW(
        hKey,
        Root,
        0,
        MAXIMUM_ALLOWED,
        &RootKey);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ErrorCode = RegDeleteKeyW(RootKey, SubKey);
    RegCloseKey(RootKey);

    return ErrorCode;
}