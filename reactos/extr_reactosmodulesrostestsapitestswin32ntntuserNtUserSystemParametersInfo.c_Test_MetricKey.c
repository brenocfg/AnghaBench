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
typedef  int /*<<< orphan*/  szReg ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_METRIC ; 
 scalar_t__ QueryUserRegValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TESTX (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 

void
Test_MetricKey(PCWSTR pwszVal, INT iVal)
{
    WCHAR szReg[10];
    DWORD cbSize;

    cbSize = sizeof(szReg);
    TESTX(QueryUserRegValueW(KEY_METRIC, pwszVal, &szReg, &cbSize, NULL) == ERROR_SUCCESS, "Value=%S\n", pwszVal);
    TESTX(_wcsicmp(szReg, L"1") == 0, "Value=%S\n", pwszVal);

}