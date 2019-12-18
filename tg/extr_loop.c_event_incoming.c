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
struct in_ev {scalar_t__ fd; int /*<<< orphan*/  refcnt; scalar_t__ bev; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct in_ev*) ; 
 int /*<<< orphan*/  vlogprintf (int /*<<< orphan*/ ,char*) ; 

void event_incoming (struct bufferevent *bev, short what, void *_arg) {
  struct in_ev *ev = _arg;
  if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
    vlogprintf (E_WARNING, "Closing incoming connection\n");
    assert (ev->fd >= 0);
    close (ev->fd);
    bufferevent_free (bev);
    ev->bev = 0;
    if (!--ev->refcnt) { free (ev); }
  }
}