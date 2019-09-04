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
typedef  int /*<<< orphan*/  PHANDLE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int DuplicateHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int IS_HKCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
Test_DuplicateHandle(void)
{
    HKEY KeyHandle, DupHandle;
    DWORD ErrorCode;
    BOOL Duplicated;

    ErrorCode = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0, KEY_READ, &KeyHandle);
    ok_dec(ErrorCode, ERROR_SUCCESS);
    ok(IS_HKCR(KeyHandle), "\n");

    Duplicated = DuplicateHandle(GetCurrentProcess(), KeyHandle, GetCurrentProcess(), (PHANDLE)&DupHandle, 0, 0, DUPLICATE_SAME_ACCESS);
    ok(Duplicated, "\n");
    ok(DupHandle != NULL, "\n");
    ok(!IS_HKCR(DupHandle), "\n");

    RegCloseKey(KeyHandle);
    RegCloseKey(DupHandle);
}