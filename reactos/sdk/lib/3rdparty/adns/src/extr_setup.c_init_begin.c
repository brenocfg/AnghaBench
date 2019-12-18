#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* adns_state ;
typedef  int adns_initflags ;
struct TYPE_7__ {int /*<<< orphan*/  wVersion; } ;
typedef  TYPE_2__ WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int iflags; int nextid; int udpsocket; int tcpsocket; int searchndots; int /*<<< orphan*/ * diagfile; scalar_t__ searchlist; int /*<<< orphan*/  tcptimeout; int /*<<< orphan*/  tcpstate; scalar_t__ tcpserver; scalar_t__ nsearchlist; scalar_t__ nsortlist; scalar_t__ nservers; scalar_t__ tcprecv_skip; int /*<<< orphan*/  tcprecv; int /*<<< orphan*/  tcpsend; scalar_t__ forallnext; int /*<<< orphan*/  output; int /*<<< orphan*/  childw; int /*<<< orphan*/  tcpw; int /*<<< orphan*/  udpw; scalar_t__ configerrno; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ ) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  adns__vbuf_init (int /*<<< orphan*/ *) ; 
 int adns_if_debug ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  server_disconnected ; 
 int /*<<< orphan*/  timerclear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_begin(adns_state *ads_r, adns_initflags flags, FILE *diagfile) {
  adns_state ads;

#ifdef ADNS_JGAA_WIN32
  WORD wVersionRequested = MAKEWORD( 2, 0 );
  WSADATA wsaData;
  int err;
#endif

  ads= malloc(sizeof(*ads)); if (!ads) return errno;

  ads->iflags= flags;
  ads->diagfile= diagfile;
  ads->configerrno= 0;
  LIST_INIT(ads->udpw);
  LIST_INIT(ads->tcpw);
  LIST_INIT(ads->childw);
  LIST_INIT(ads->output);
  ads->forallnext= 0;
  ads->nextid= 0x311f;
  ads->udpsocket= ads->tcpsocket= -1;
  adns__vbuf_init(&ads->tcpsend);
  adns__vbuf_init(&ads->tcprecv);
  ads->tcprecv_skip= 0;
  ads->nservers= ads->nsortlist= ads->nsearchlist= ads->tcpserver= 0;
  ads->searchndots= 1;
  ads->tcpstate= server_disconnected;
  timerclear(&ads->tcptimeout);
  ads->searchlist= 0;

 #ifdef ADNS_JGAA_WIN32
  err= WSAStartup( wVersionRequested, &wsaData );
  if ( err != 0 ) {
    if (ads->diagfile && ads->iflags & adns_if_debug)
      fprintf(ads->diagfile,"adns: WSAStartup() failed. \n");
    return -1;}
  if (LOBYTE( wsaData.wVersion ) != 2 ||
    HIBYTE( wsaData.wVersion ) != 0 ) {
    if (ads->diagfile && ads->iflags & adns_if_debug)
      fprintf(ads->diagfile,"adns: Need Winsock 2.0 or better!\n");

    WSACleanup();
    return -1;}

  /* The WinSock DLL is acceptable. Proceed. */
#endif

  *ads_r= ads;

  return 0;
}