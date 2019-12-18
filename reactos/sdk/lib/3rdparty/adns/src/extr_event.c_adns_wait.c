#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  TYPE_1__* adns_state ;
typedef  int /*<<< orphan*/  adns_query ;
typedef  int /*<<< orphan*/  adns_answer ;
struct TYPE_9__ {int iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADNS_CAPTURE_ERRNO ; 
 int /*<<< orphan*/  ADNS_CLEAR_ERRNO ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns__consistency (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__diag (TYPE_1__*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int adns__internal_check (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  adns_afterselect (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns_beforeselect (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval**,struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns_globalsystemfailure (TYPE_1__*) ; 
 int adns_if_eintr ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cc_entex ; 
 int errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int) ; 

int adns_wait(adns_state ads,
	      adns_query *query_io,
	      adns_answer **answer_r,
	      void **context_r) {
  int r, maxfd, rsel;
  fd_set readfds, writefds, exceptfds;
  struct timeval tvbuf, *tvp;

  adns__consistency(ads,*query_io,cc_entex);
  for (;;) {
    r= adns__internal_check(ads,query_io,answer_r,context_r);
    if (r != EAGAIN) break;
    maxfd= 0; tvp= 0;
    FD_ZERO(&readfds); FD_ZERO(&writefds); FD_ZERO(&exceptfds);
    adns_beforeselect(ads,&maxfd,&readfds,&writefds,&exceptfds,&tvp,&tvbuf,0);
    assert(tvp);
	ADNS_CLEAR_ERRNO;
    rsel= select(maxfd,&readfds,&writefds,&exceptfds,tvp);
	ADNS_CAPTURE_ERRNO;
    if (rsel==-1) {
      if (errno == EINTR) {
	if (ads->iflags & adns_if_eintr) { r= EINTR; break; }
      } else {
	adns__diag(ads,-1,0,"select failed in wait: %s",strerror(errno));
	adns_globalsystemfailure(ads);
      }
    } else {
      assert(rsel >= 0);
      adns_afterselect(ads,maxfd,&readfds,&writefds,&exceptfds,0);
    }
  }
  adns__consistency(ads,0,cc_entex);
  return r;
}