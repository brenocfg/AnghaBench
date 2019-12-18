#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  adns_query ;
typedef  int /*<<< orphan*/  adns_answer ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct TYPE_3__ {int /*<<< orphan*/  qu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADNS_CAPTURE_ERRNO ; 
 int /*<<< orphan*/  ADNS_CLEAR_ERRNO ; 
 int EAGAIN ; 
 scalar_t__ EINTR ; 
 int ESRCH ; 
 int EWOULDBLOCK ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns_afterselect (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns_beforeselect (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval**,struct timeval*,int /*<<< orphan*/ ) ; 
 int adns_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  ads ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ensure_adns_init () ; 
 scalar_t__ errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outerr () ; 
 TYPE_2__ outstanding ; 
 scalar_t__ ov_asynch ; 
 scalar_t__ ov_pipe ; 
 int /*<<< orphan*/  process_optarg (char const*,char const* const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_done (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quitnow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcode ; 
 int /*<<< orphan*/  read_stdin () ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysfail (char*,scalar_t__) ; 
 int /*<<< orphan*/  usageerr (char*) ; 

int main(int argc, const char *const *argv) {
  struct timeval *tv, tvbuf;
  adns_query qu;
  void *qun_v;
  adns_answer *answer;
  int r, maxfd;
  fd_set readfds, writefds, exceptfds;
  const char *arg;

  ensure_adns_init();

  while ((arg= *++argv)) process_optarg(arg,&argv,0);

  if (!ov_pipe && !ads) usageerr("no domains given, and -f/--pipe not used; try --help");

  for (;;) {
    for (;;) {
      qu= ov_asynch ? 0 : outstanding.head ? outstanding.head->qu : 0;
      r= adns_check(ads,&qu,&answer,&qun_v);
      if ((r == EAGAIN) || (r == EWOULDBLOCK)) break;
      if (r == ESRCH) { if (!ov_pipe) goto x_quit; else break; }
      assert(!r);
      query_done(qun_v,answer);
    }
    maxfd= 0;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);
    if (ov_pipe) {
      maxfd= 1;
      FD_SET(0,&readfds);
    }
    tv= 0;
    adns_beforeselect(ads, &maxfd, &readfds,&writefds,&exceptfds, &tv,&tvbuf,0);
	ADNS_CLEAR_ERRNO;
    r= select(maxfd, &readfds,&writefds,&exceptfds, tv);
	ADNS_CAPTURE_ERRNO;
    if (r == -1) {
      if (errno == EINTR) continue;
      sysfail("select",errno);
    }
    adns_afterselect(ads, maxfd, &readfds,&writefds,&exceptfds, 0);
    if (ov_pipe && FD_ISSET(0,&readfds)) read_stdin();
  }
x_quit:
  if (fclose(stdout)) outerr();
  quitnow(rcode);
}