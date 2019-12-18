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
struct timeval {int dummy; } ;
struct pollfd {int fd; int revents; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int ADNS_SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  POLLPRI ; 
 int /*<<< orphan*/  adns_processexceptional ; 
 int /*<<< orphan*/  adns_processreadable ; 
 int /*<<< orphan*/  adns_processwriteable ; 
 int /*<<< orphan*/  fd_event (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct timeval,int*) ; 

void adns__fdevents(adns_state ads,
		    const struct pollfd *pollfds, int npollfds,
		    int maxfd, const fd_set *readfds,
		    const fd_set *writefds, const fd_set *exceptfds,
		    struct timeval now, int *r_r) {
  int i, revents;
  ADNS_SOCKET fd;

  for (i=0; i<npollfds; i++) {
    fd= pollfds[i].fd;
    if ((int)fd >= maxfd) maxfd= fd+1;
    revents= pollfds[i].revents;
    fd_event(ads,fd, revents,POLLIN, maxfd,readfds, adns_processreadable,now,r_r);
    fd_event(ads,fd, revents,POLLOUT, maxfd,writefds, adns_processwriteable,now,r_r);
    fd_event(ads,fd, revents,POLLPRI, maxfd,exceptfds, adns_processexceptional,now,r_r);
  }
}