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
typedef  int /*<<< orphan*/  is_app_container ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_FUNCTION ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 int GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TokenIsAppContainer ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_GetTokenInformation(void)
{
    DWORD is_app_container, size;
    HANDLE token;
    BOOL ret;

    ret = OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &token);
    ok(ret, "OpenProcessToken failed: %u\n", GetLastError());

    size = 0;
    is_app_container = 0xdeadbeef;
    ret = GetTokenInformation(token, TokenIsAppContainer, &is_app_container,
                              sizeof(is_app_container), &size);
    ok(ret || broken(GetLastError() == ERROR_INVALID_PARAMETER ||
                     GetLastError() == ERROR_INVALID_FUNCTION), /* pre-win8 */
       "GetTokenInformation failed: %u\n", GetLastError());
    if(ret) {
        ok(size == sizeof(is_app_container), "size = %u\n", size);
        ok(!is_app_container, "is_app_container = %x\n", is_app_container);
    }

    CloseHandle(token);
}