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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int WAIT_OBJECT_0 ; 
 int WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _beginthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  test_thread_func ; 
 int /*<<< orphan*/  test_thread_func_ex ; 

__attribute__((used)) static void test_thread_handle_close(void)
{
    HANDLE hThread;
    DWORD ret;

    /* _beginthread: handle is not closed on ExitThread and _endthreadex */
    hThread = (HANDLE)_beginthread(test_thread_func, 0, NULL);
    ok(hThread != INVALID_HANDLE_VALUE, "_beginthread failed (%d)\n", errno);
    WaitForSingleObject(hThread, INFINITE);
    ret = CloseHandle(hThread);
    ok(!ret, "ret = %d\n", ret);

    hThread = (HANDLE)_beginthread(test_thread_func, 0, (void*)1);
    ok(hThread != INVALID_HANDLE_VALUE, "_beginthread failed (%d)\n", errno);
    WaitForSingleObject(hThread, INFINITE);
    ret = CloseHandle(hThread);
    ok(!ret, "ret = %d\n", ret);

    hThread = (HANDLE)_beginthread(test_thread_func, 0, (void*)2);
    ok(hThread != INVALID_HANDLE_VALUE, "_beginthread failed (%d)\n", errno);
    Sleep(150);
    ret = WaitForSingleObject(hThread, INFINITE);
    ok(ret == WAIT_OBJECT_0, "ret = %d\n", ret);
    ret = CloseHandle(hThread);
    ok(ret, "ret = %d\n", ret);

    hThread = (HANDLE)_beginthread(test_thread_func, 0, (void*)3);
    ok(hThread != INVALID_HANDLE_VALUE, "_beginthread failed (%d)\n", errno);
    Sleep(150);
    ret = WaitForSingleObject(hThread, INFINITE);
    ok(ret == WAIT_OBJECT_0, "ret = %d\n", ret);
    ret = CloseHandle(hThread);
    ok(ret, "ret = %d\n", ret);

    /* _beginthreadex: handle is not closed on _endthread */
    hThread = (HANDLE)_beginthreadex(NULL,0, test_thread_func_ex, NULL, 0, NULL);
    ok(hThread != NULL, "_beginthreadex failed (%d)\n", errno);
    Sleep(150);
    ret = WaitForSingleObject(hThread, INFINITE);
    ok(ret == WAIT_OBJECT_0, "ret = %d\n", ret);
    ret = CloseHandle(hThread);
    ok(ret, "ret = %d\n", ret);
}