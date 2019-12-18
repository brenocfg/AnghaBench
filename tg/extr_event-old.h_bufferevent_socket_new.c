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
struct event_base {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bufferevent_base_set (struct event_base*,struct bufferevent*) ; 
 struct bufferevent* bufferevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bufferevent *bufferevent_socket_new (struct event_base *base, int fd, int flags) {
  assert (!flags);
  struct bufferevent *bev = bufferevent_new(fd, 0, 0, 0, 0);
  bufferevent_base_set (base, bev);
  return bev;
}