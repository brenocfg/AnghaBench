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

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_event ; 
 int /*<<< orphan*/  conn_close_event ; 
 int /*<<< orphan*/  conn_wait_event ; 
 int /*<<< orphan*/  request_sent_event ; 
 int /*<<< orphan*/  server_req_rec_event ; 

__attribute__((used)) static void free_events(void)
{
    CloseHandle(complete_event);
    CloseHandle(conn_close_event);
    CloseHandle(conn_wait_event);
    CloseHandle(server_req_rec_event);
    CloseHandle(request_sent_event);
}