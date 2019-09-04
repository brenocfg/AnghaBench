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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/ * PETHREAD ;
typedef  int /*<<< orphan*/  KDSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  KDDBGPRINT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdb_input ; 
 int /*<<< orphan*/  hex_to_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hex_to_tid (scalar_t__) ; 
 int /*<<< orphan*/  send_gdb_packet (char*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static
KDSTATUS
handle_gdb_thread_alive(void)
{
    ULONG_PTR Pid, Tid;
    PETHREAD Thread;
    KDSTATUS Status;

#if MONOPROCESS
    Pid = 0;
    Tid = hex_to_tid(&gdb_input[1]);

    KDDBGPRINT("Checking if %p is alive.\n", Tid);

#else
    Pid = hex_to_pid(&gdb_input[2]);
    Tid = hex_to_tid(strstr(gdb_input, ".") + 1);

    /* We cannot use PsLookupProcessThreadByCid as we could be running at any IRQL.
     * So loop. */
    KDDBGPRINT("Checking if p%p.%p is alive.\n", Pid, Tid);
#endif

    Thread = find_thread(Pid, Tid);

    if (Thread != NULL)
        Status = send_gdb_packet("OK");
    else
        Status = send_gdb_packet("E03");

    return Status;
}