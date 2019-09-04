#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct tmuxpeer {TYPE_1__ ibuf; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tmuxpeer*) ; 
 int /*<<< orphan*/  imsg_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,struct tmuxpeer*) ; 

void
proc_remove_peer(struct tmuxpeer *peer)
{
	log_debug("remove peer %p", peer);

	event_del(&peer->event);
	imsg_clear(&peer->ibuf);

	close(peer->ibuf.fd);
	free(peer);
}