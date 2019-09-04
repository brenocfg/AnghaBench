#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int byte ;
typedef  TYPE_2__* adns_state ;
typedef  TYPE_3__* adns_query ;
struct TYPE_13__ {scalar_t__ used; } ;
struct TYPE_12__ {scalar_t__ state; int query_dglen; int* query_dgram; TYPE_2__* ads; int /*<<< orphan*/  retries; } ;
struct TYPE_10__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_11__ {scalar_t__ tcpstate; TYPE_4__ tcpsend; int /*<<< orphan*/  tcpsocket; TYPE_1__ tcptimeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADNS_CAPTURE_ERRNO ; 
 int /*<<< orphan*/  ADNS_CLEAR_ERRNO ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ ENOSPC ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  adns__sigpipe_protect (TYPE_2__*) ; 
 int /*<<< orphan*/  adns__sigpipe_unprotect (TYPE_2__*) ; 
 int /*<<< orphan*/  adns__tcp_broken (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int adns__vbuf_append (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  adns__vbuf_ensure (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ query_tcpw ; 
 scalar_t__ server_ok ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int writev (int /*<<< orphan*/ ,struct iovec*,int) ; 

void adns__querysend_tcp(adns_query qu, struct timeval now) {
  byte length[2];
  struct iovec iov[2];
  int wr, r;
  adns_state ads;

  if (qu->ads->tcpstate != server_ok) return;

  assert(qu->state == query_tcpw);

  length[0]= (qu->query_dglen&0x0ff00U) >>8;
  length[1]= (qu->query_dglen&0x0ff);

  ads= qu->ads;
  if (!adns__vbuf_ensure(&ads->tcpsend,ads->tcpsend.used+qu->query_dglen+2)) return;

  qu->retries++;

  /* Reset idle timeout. */
  ads->tcptimeout.tv_sec= ads->tcptimeout.tv_usec= 0;

  if (ads->tcpsend.used) {
    wr= 0;
  } else {
    iov[0].iov_base= (char*)length;
    iov[0].iov_len= 2;
    iov[1].iov_base= (char*)qu->query_dgram;
    iov[1].iov_len= qu->query_dglen;
    adns__sigpipe_protect(qu->ads);

    ADNS_CLEAR_ERRNO;
    wr= writev(qu->ads->tcpsocket,iov,2);
    ADNS_CAPTURE_ERRNO;
    adns__sigpipe_unprotect(qu->ads);
    if (wr < 0) {
      if (!(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR || errno == ENOSPC ||
	    errno == ENOBUFS || errno == ENOMEM)) {
	adns__tcp_broken(ads,"write",strerror(errno));
	return;
      }
      wr= 0;
    }
  }

  if (wr<2) {
    r= adns__vbuf_append(&ads->tcpsend,length,2-wr); assert(r);
    wr= 0;
  } else {
    wr-= 2;
  }
  if (wr<qu->query_dglen) {
    r= adns__vbuf_append(&ads->tcpsend,qu->query_dgram+wr,qu->query_dglen-wr); assert(r);
  }
}