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
struct tmuxproc {int dummy; } ;
struct tmuxpeer {void (* dispatchcb ) (struct imsg*,void*) ;int /*<<< orphan*/  event; int /*<<< orphan*/  ibuf; void* arg; struct tmuxproc* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmuxpeer*) ; 
 int /*<<< orphan*/  imsg_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_debug (char*,struct tmuxpeer*,int,void*) ; 
 int /*<<< orphan*/  proc_event_cb ; 
 int /*<<< orphan*/  proc_update_event (struct tmuxpeer*) ; 
 struct tmuxpeer* xcalloc (int,int) ; 

struct tmuxpeer *
proc_add_peer(struct tmuxproc *tp, int fd,
    void (*dispatchcb)(struct imsg *, void *), void *arg)
{
	struct tmuxpeer	*peer;

	peer = xcalloc(1, sizeof *peer);
	peer->parent = tp;

	peer->dispatchcb = dispatchcb;
	peer->arg = arg;

	imsg_init(&peer->ibuf, fd);
	event_set(&peer->event, fd, EV_READ, proc_event_cb, peer);

	log_debug("add peer %p: %d (%p)", peer, fd, arg);

	proc_update_event(peer);
	return (peer);
}