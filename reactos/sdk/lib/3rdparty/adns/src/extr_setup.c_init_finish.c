#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct protoent {int /*<<< orphan*/  p_proto; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  TYPE_1__* adns_state ;
struct TYPE_6__ {int iflags; scalar_t__ udpsocket; scalar_t__ diagfile; int /*<<< orphan*/  nservers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADNS_CAPTURE_ERRNO ; 
 int /*<<< orphan*/  ADNS_CLEAR_ERRNO ; 
 int /*<<< orphan*/  AF_INET ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  addserver (TYPE_1__*,struct in_addr) ; 
 int adns__setnonblock (TYPE_1__*,scalar_t__) ; 
 int adns_if_debug ; 
 int /*<<< orphan*/  adns_socket_close (scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct protoent* getprotobyname (char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_finish(adns_state ads) {
  struct protoent *proto;
  int r;
/* Don't add loopback on ReactOS it slows down queries to non existent server */
#ifndef __REACTOS__
  struct in_addr ia;
  if (!ads->nservers) {
    if (ads->diagfile && ads->iflags & adns_if_debug)
      fprintf(ads->diagfile,"adns: no nameservers, using localhost\n");
    ia.s_addr= htonl(INADDR_LOOPBACK);
    addserver(ads,ia);
  }
#endif
  proto= getprotobyname("udp"); if (!proto) { r= ENOPROTOOPT; goto x_free; }
  ADNS_CLEAR_ERRNO;
  ads->udpsocket= socket(AF_INET,SOCK_DGRAM,proto->p_proto);
  ADNS_CAPTURE_ERRNO;
  if (ads->udpsocket<0) { r= errno; goto x_free; }

  r= adns__setnonblock(ads,ads->udpsocket);
  if (r) { r= errno; goto x_closeudp; }
  return 0;

 x_closeudp:
  adns_socket_close(ads->udpsocket);
 x_free:
  free(ads);
#ifdef ADNS_JGAA_WIN32
  WSACleanup();
#endif /* WIN32 */
  return r;
}