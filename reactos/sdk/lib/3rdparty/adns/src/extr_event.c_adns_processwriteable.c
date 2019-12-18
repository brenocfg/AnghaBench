#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  TYPE_2__* adns_state ;
struct TYPE_12__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  used; } ;
struct TYPE_10__ {int used; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {int tcpstate; TYPE_1__ tcpsend; int /*<<< orphan*/  tcpsocket; TYPE_5__ tcprecv; int /*<<< orphan*/  tcprecv_skip; } ;
typedef  int /*<<< orphan*/  ADNS_SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  ADNS_CAPTURE_ERRNO ; 
 int /*<<< orphan*/  ADNS_CLEAR_ERRNO ; 
 int EAGAIN ; 
 int EINTR ; 
 int ENOMEM ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  adns__consistency (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__sigpipe_protect (TYPE_2__*) ; 
 int /*<<< orphan*/  adns__sigpipe_unprotect (TYPE_2__*) ; 
 int /*<<< orphan*/  adns__tcp_broken (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  adns__vbuf_ensure (TYPE_5__*,int) ; 
 int adns_socket_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int adns_socket_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cc_entex ; 
 int errno ; 
 int /*<<< orphan*/  errno_resources (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
#define  server_broken 131 
#define  server_connecting 130 
#define  server_disconnected 129 
#define  server_ok 128 
 char* strerror (int) ; 
 int /*<<< orphan*/  tcp_connected (TYPE_2__*,struct timeval const) ; 

int adns_processwriteable(adns_state ads, ADNS_SOCKET fd, const struct timeval *now) {
  int r;

  adns__consistency(ads,0,cc_entex);

  switch (ads->tcpstate) {
  case server_disconnected:
  case server_broken:
    break;
  case server_connecting:
    if (fd != ads->tcpsocket) break;
    assert(ads->tcprecv.used==0);
    assert(ads->tcprecv_skip==0);
    for (;;) {
      if (!adns__vbuf_ensure(&ads->tcprecv,1)) { r= ENOMEM; goto xit; }
	  ADNS_CLEAR_ERRNO;
      r= adns_socket_read(ads->tcpsocket,&ads->tcprecv.buf,1);
	  ADNS_CAPTURE_ERRNO;
      if (r==0 || (r<0 && (errno==EAGAIN || errno==EWOULDBLOCK))) {
	tcp_connected(ads,*now);
	r= 0; goto xit;
      }
      if (r>0) {
	adns__tcp_broken(ads,"connect/adns_socket_read","sent data before first request");
	r= 0; goto xit;
      }
      if (errno==EINTR) continue;
      if (errno_resources(errno)) { r= errno; goto xit; }
      adns__tcp_broken(ads,"connect/adns_socket_read",strerror(errno));
      r= 0; goto xit;
    } /* not reached */
  case server_ok:
    if (fd != ads->tcpsocket) break;
    while (ads->tcpsend.used) {
      adns__sigpipe_protect(ads);
	  ADNS_CLEAR_ERRNO;
      r= adns_socket_write(ads->tcpsocket,ads->tcpsend.buf,ads->tcpsend.used);
	  ADNS_CAPTURE_ERRNO;
      adns__sigpipe_unprotect(ads);
      if (r<0) {
	if (errno==EINTR) continue;
	if (errno==EAGAIN || errno==EWOULDBLOCK) { r= 0; goto xit; }
	if (errno_resources(errno)) { r= errno; goto xit; }
	adns__tcp_broken(ads,"adns_socket_write",strerror(errno));
	r= 0; goto xit;
      } else if (r>0) {
	ads->tcpsend.used -= r;
	memmove(ads->tcpsend.buf,ads->tcpsend.buf+r, (size_t) ads->tcpsend.used);
      }
    }
    r= 0;
    goto xit;
  default:
    abort();
  }
  r= 0;
xit:
  adns__consistency(ads,0,cc_entex);
  return r;
}