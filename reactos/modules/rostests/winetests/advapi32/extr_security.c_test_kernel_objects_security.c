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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ DuplicateToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SecurityImpersonation ; 
 int TOKEN_DUPLICATE ; 
 int TOKEN_QUERY ; 
 scalar_t__ TokenImpersonation ; 
 scalar_t__ TokenPrimary ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_event_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_file_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_filemap_security () ; 
 int /*<<< orphan*/  test_mutex_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_named_pipe_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_process_access () ; 
 int /*<<< orphan*/  test_semaphore_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_security () ; 
 scalar_t__ validate_impersonation_token (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void test_kernel_objects_security(void)
{
    HANDLE token, process_token;
    DWORD ret, token_type;

    ret = OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_QUERY, &process_token);
    ok(ret, "OpenProcessToken error %d\n", GetLastError());

    ret = validate_impersonation_token(process_token, &token_type);
    ok(token_type == TokenPrimary, "expected TokenPrimary, got %d\n", token_type);
    ok(!ret, "access token should not be an impersonation token\n");

    ret = DuplicateToken(process_token, SecurityImpersonation, &token);
    ok(ret, "DuplicateToken error %d\n", GetLastError());

    ret = validate_impersonation_token(token, &token_type);
    ok(ret, "access token should be a valid impersonation token\n");
    ok(token_type == TokenImpersonation, "expected TokenImpersonation, got %d\n", token_type);

    test_mutex_security(token);
    test_event_security(token);
    test_named_pipe_security(token);
    test_semaphore_security(token);
    test_file_security(token);
    test_filemap_security();
    test_thread_security();
    test_process_access();
    /* FIXME: test other kernel object types */

    CloseHandle(process_token);
    CloseHandle(token);
}