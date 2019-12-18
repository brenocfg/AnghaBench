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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventW (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateSemaphoreW (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ FALSE ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_FLAG_DELETE_ON_CLOSE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ ReleaseSemaphore (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int ResetEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ SignalObjectAndWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_signalandwait(void)
{
    DWORD r;
    HANDLE event[2], semaphore[2], file;
    int i;

    /* invalid parameters */
    r = SignalObjectAndWait(NULL, NULL, 0, 0);
    ok( r == WAIT_FAILED, "should fail\n");

    event[0] = CreateEventW(NULL, 0, 0, NULL);
    event[1] = CreateEventW(NULL, 1, 1, NULL);

    ok( event[0] && event[1], "failed to create event flags\n");

    r = SignalObjectAndWait(event[0], NULL, 0, FALSE);
    ok( r == WAIT_FAILED, "should fail\n");

    r = SignalObjectAndWait(NULL, event[0], 0, FALSE);
    ok( r == WAIT_FAILED, "should fail\n");


    /* valid parameters */
    r = SignalObjectAndWait(event[0], event[1], 0, FALSE);
    ok( r == WAIT_OBJECT_0, "should succeed\n");

    /* event[0] is now signalled - we repeat this test multiple times
     * to ensure that the wineserver handles this situation properly. */
    for (i = 0; i < 10000; i++)
    {
        r = SignalObjectAndWait(event[0], event[0], 0, FALSE);
        ok(r == WAIT_OBJECT_0, "should succeed\n");
    }

    /* event[0] is not signalled */
    r = WaitForSingleObject(event[0], 0);
    ok( r == WAIT_TIMEOUT, "event was signalled\n");

    r = SignalObjectAndWait(event[0], event[0], 0, FALSE);
    ok( r == WAIT_OBJECT_0, "should succeed\n");

    /* clear event[1] and check for a timeout */
    ok(ResetEvent(event[1]), "failed to clear event[1]\n");
    r = SignalObjectAndWait(event[0], event[1], 0, FALSE);
    ok( r == WAIT_TIMEOUT, "should timeout\n");

    CloseHandle(event[0]);
    CloseHandle(event[1]);

    /* semaphores */
    semaphore[0] = CreateSemaphoreW( NULL, 0, 1, NULL );
    semaphore[1] = CreateSemaphoreW( NULL, 1, 1, NULL );
    ok( semaphore[0] && semaphore[1], "failed to create semaphore\n");

    r = SignalObjectAndWait(semaphore[0], semaphore[1], 0, FALSE);
    ok( r == WAIT_OBJECT_0, "should succeed\n");

    r = SignalObjectAndWait(semaphore[0], semaphore[1], 0, FALSE);
    ok( r == WAIT_FAILED, "should fail\n");

    r = ReleaseSemaphore(semaphore[0],1,NULL);
    ok( r == FALSE, "should fail\n");

    r = ReleaseSemaphore(semaphore[1],1,NULL);
    ok( r == TRUE, "should succeed\n");

    CloseHandle(semaphore[0]);
    CloseHandle(semaphore[1]);

    /* try a registry key */
    file = CreateFileA("x", GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_DELETE_ON_CLOSE, NULL);
    r = SignalObjectAndWait(file, file, 0, FALSE);
    ok( r == WAIT_FAILED, "should fail\n");
    ok( ERROR_INVALID_HANDLE == GetLastError(), "should return invalid handle error\n");
    CloseHandle(file);
}