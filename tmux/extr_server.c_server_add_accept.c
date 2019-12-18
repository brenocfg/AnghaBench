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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_accept ; 
 int /*<<< orphan*/  server_ev_accept ; 
 int server_fd ; 

void
server_add_accept(int timeout)
{
	struct timeval tv = { timeout, 0 };

	if (server_fd == -1)
		return;

	if (event_initialized(&server_ev_accept))
		event_del(&server_ev_accept);

	if (timeout == 0) {
		event_set(&server_ev_accept, server_fd, EV_READ, server_accept,
		    NULL);
		event_add(&server_ev_accept, NULL);
	} else {
		event_set(&server_ev_accept, server_fd, EV_TIMEOUT,
		    server_accept, NULL);
		event_add(&server_ev_accept, &tv);
	}
}