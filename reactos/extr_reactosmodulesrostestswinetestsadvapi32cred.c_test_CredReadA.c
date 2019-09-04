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
typedef  int /*<<< orphan*/  PCREDENTIALA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CRED_TYPE_GENERIC ; 
 scalar_t__ ERROR_INVALID_FLAGS ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * TEST_TARGET_NAME ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCredReadA (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_CredReadA(void)
{
    BOOL ret;
    PCREDENTIALA cred;

    SetLastError(0xdeadbeef);
    ret = pCredReadA(TEST_TARGET_NAME, -1, 0, &cred);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "CredReadA should have failed with ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    SetLastError(0xdeadbeef);
    ret = pCredReadA(TEST_TARGET_NAME, CRED_TYPE_GENERIC, 0xdeadbeef, &cred);
    ok(!ret && ( GetLastError() == ERROR_INVALID_FLAGS || GetLastError() == ERROR_INVALID_PARAMETER ),
        "CredReadA should have failed with ERROR_INVALID_FLAGS or ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());

    SetLastError(0xdeadbeef);
    ret = pCredReadA(NULL, CRED_TYPE_GENERIC, 0, &cred);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
        "CredReadA should have failed with ERROR_INVALID_PARAMETER instead of %d\n",
        GetLastError());
}