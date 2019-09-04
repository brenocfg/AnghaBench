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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  threadfunc ; 

int main(int ac, char **av)
{
	DWORD id;
	HANDLE Thread;

	Thread = CreateThread(0, 0, threadfunc, 0, 0, &id);
	printf("Main: ThreadId for new thread is %08lx\n", id);
	printf("Main: Waiting on thread...\n");
	WaitForSingleObject(Thread, INFINITE);
	printf("Main: OK, somebody fixed the PsUnblockThread spinlock double-acquire crash\n");
	NtClose(Thread);
	printf("Main: Terminating...\n");
	return 0;
}