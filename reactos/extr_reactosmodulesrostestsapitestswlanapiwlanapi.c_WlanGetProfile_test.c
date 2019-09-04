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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  InterfaceGuid ; 
 scalar_t__ WlanGetProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void WlanGetProfile_test(void)
{
    DWORD ret;
    WCHAR *strProfileXml;

    /* invalid pReserved */
    ret = WlanGetProfile((HANDLE) -1, &InterfaceGuid, L"", (PVOID) 1, &strProfileXml, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid InterfaceGuid */
    ret = WlanGetProfile((HANDLE) -1, NULL, L"test", NULL, &strProfileXml, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");

    /* invalid pstrProfileXml */
    ret = WlanGetProfile((HANDLE) -1, &InterfaceGuid, L"test", NULL, NULL, NULL, NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "expected failure\n");
}