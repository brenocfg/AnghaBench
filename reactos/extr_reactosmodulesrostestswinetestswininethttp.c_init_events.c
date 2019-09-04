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
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 void* complete_event ; 
 void* conn_close_event ; 
 void* conn_wait_event ; 
 void* request_sent_event ; 
 void* server_req_rec_event ; 

__attribute__((used)) static void init_events(void)
{
    complete_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    conn_close_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    conn_wait_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    server_req_rec_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    request_sent_event = CreateEventW(NULL, FALSE, FALSE, NULL);
}