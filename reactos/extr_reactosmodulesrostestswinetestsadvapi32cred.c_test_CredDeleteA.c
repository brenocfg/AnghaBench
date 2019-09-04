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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CRED_TYPE_GENERIC ; 
 scalar_t__ ERROR_INVALID_FLAGS ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TEST_TARGET_NAME ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCredDeleteA (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void test_CredDeleteA(void)
{
    BOOL ret;

    SetLastError(0xdeadbeef);
    ret = pCredDeleteA(TEST_TARGET_NAME, -1, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "CredDeleteA should have failed with ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    SetLastError(0xdeadbeef);
    ret = pCredDeleteA(TEST_TARGET_NAME, CRED_TYPE_GENERIC, 0xdeadbeef);
    ok(!ret && ( GetLastError() == ERROR_INVALID_FLAGS || GetLastError() == ERROR_INVALID_PARAMETER /* Vista */ ),
        "CredDeleteA should have failed with ERROR_INVALID_FLAGS or ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());
}