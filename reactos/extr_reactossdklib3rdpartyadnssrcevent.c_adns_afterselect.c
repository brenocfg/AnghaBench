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
struct pollfd {int revents; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int MAX_POLLFDS ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int /*<<< orphan*/  adns__consistency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__fdevents (int /*<<< orphan*/ ,struct pollfd*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct timeval const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__must_gettimeofday (int /*<<< orphan*/ ,struct timeval const**,struct timeval*) ; 
 int adns__pollfds (int /*<<< orphan*/ ,struct pollfd*) ; 
 int /*<<< orphan*/  adns_processtimeouts (int /*<<< orphan*/ ,struct timeval const*) ; 
 int /*<<< orphan*/  cc_entex ; 

void adns_afterselect(adns_state ads, int maxfd, const fd_set *readfds,
		      const fd_set *writefds, const fd_set *exceptfds,
		      const struct timeval *now) {
  struct timeval tv_buf;
  struct pollfd pollfds[MAX_POLLFDS];
  int npollfds, i;

  adns__consistency(ads,0,cc_entex);
  adns__must_gettimeofday(ads,&now,&tv_buf);
  if (!now) goto xit;
  adns_processtimeouts(ads,now);

  npollfds= adns__pollfds(ads,pollfds);
  for (i=0; i<npollfds; i++) pollfds[i].revents= POLLIN|POLLOUT|POLLPRI;
  adns__fdevents(ads,
		 pollfds,npollfds,
		 maxfd,readfds,writefds,exceptfds,
		 *now, 0);
xit:
  adns__consistency(ads,0,cc_entex);
}