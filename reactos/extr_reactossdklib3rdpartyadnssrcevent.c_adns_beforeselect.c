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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct pollfd {int fd; int events; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int ADNS_SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int MAX_POLLFDS ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int /*<<< orphan*/  adns__consistency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__must_gettimeofday (int /*<<< orphan*/ ,struct timeval const**,struct timeval*) ; 
 int adns__pollfds (int /*<<< orphan*/ ,struct pollfd*) ; 
 int /*<<< orphan*/  adns__timeouts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval**,struct timeval*,struct timeval const) ; 
 int /*<<< orphan*/  cc_entex ; 
 int /*<<< orphan*/  inter_immed (struct timeval**,struct timeval*) ; 

void adns_beforeselect(adns_state ads, int *maxfd_io, fd_set *readfds_io,
		       fd_set *writefds_io, fd_set *exceptfds_io,
		       struct timeval **tv_mod, struct timeval *tv_tobuf,
		       const struct timeval *now) {
  struct timeval tv_nowbuf;
  struct pollfd pollfds[MAX_POLLFDS];
  int i, maxfd, npollfds;
  ADNS_SOCKET fd;

  adns__consistency(ads,0,cc_entex);

  if (tv_mod && (!*tv_mod || (*tv_mod)->tv_sec || (*tv_mod)->tv_usec)) {
    /* The caller is planning to sleep. */
    adns__must_gettimeofday(ads,&now,&tv_nowbuf);
    if (!now) { inter_immed(tv_mod,tv_tobuf); goto xit; }
    adns__timeouts(ads, 0, tv_mod,tv_tobuf, *now);
  }

  npollfds= adns__pollfds(ads,pollfds);
  maxfd= *maxfd_io;
  for (i=0; i<npollfds; i++) {
    fd= pollfds[i].fd;
    if ((int)fd >= maxfd) maxfd= fd+1;
    if (pollfds[i].events & POLLIN) FD_SET(fd,readfds_io);
    if (pollfds[i].events & POLLOUT) FD_SET(fd,writefds_io);
    if (pollfds[i].events & POLLPRI) FD_SET(fd,exceptfds_io);
  }
  *maxfd_io= maxfd;

xit:
  adns__consistency(ads,0,cc_entex);
}