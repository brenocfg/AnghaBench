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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__) ; 

__attribute__((used)) static void test_null_source(void)
{
    int len;
    DWORD GLE;

    SetLastError(0);
    len = WideCharToMultiByte(CP_ACP, 0, NULL, 0, NULL, 0, NULL, NULL);
    GLE = GetLastError();
    ok(!len && GLE == ERROR_INVALID_PARAMETER,
        "WideCharToMultiByte returned %d with GLE=%u (expected 0 with ERROR_INVALID_PARAMETER)\n",
        len, GLE);

    SetLastError(0);
    len = WideCharToMultiByte(CP_ACP, 0, NULL, -1, NULL, 0, NULL, NULL);
    GLE = GetLastError();
    ok(!len && GLE == ERROR_INVALID_PARAMETER,
        "WideCharToMultiByte returned %d with GLE=%u (expected 0 with ERROR_INVALID_PARAMETER)\n",
        len, GLE);
}