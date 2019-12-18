#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* adns_state ;
struct TYPE_13__ {scalar_t__ head; } ;
struct TYPE_12__ {scalar_t__ head; } ;
struct TYPE_11__ {scalar_t__ head; } ;
struct TYPE_10__ {scalar_t__ head; } ;
struct TYPE_14__ {int udpsocket; int tcpsocket; int /*<<< orphan*/  tcprecv; int /*<<< orphan*/  tcpsend; TYPE_4__ output; TYPE_3__ childw; TYPE_2__ tcpw; TYPE_1__ udpw; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  adns__consistency (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__vbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns_cancel (scalar_t__) ; 
 int /*<<< orphan*/  adns_socket_close (int) ; 
 int /*<<< orphan*/  cc_entex ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  freesearchlist (TYPE_5__*) ; 

void adns_finish(adns_state ads) {
  adns__consistency(ads,0,cc_entex);
  for (;;) {
    if (ads->udpw.head) adns_cancel(ads->udpw.head);
    else if (ads->tcpw.head) adns_cancel(ads->tcpw.head);
    else if (ads->childw.head) adns_cancel(ads->childw.head);
    else if (ads->output.head) adns_cancel(ads->output.head);
    else break;
  }
  adns_socket_close(ads->udpsocket);
  if (ads->tcpsocket != -1) adns_socket_close(ads->tcpsocket);
  adns__vbuf_free(&ads->tcpsend);
  adns__vbuf_free(&ads->tcprecv);
  freesearchlist(ads);
  free(ads);
#ifdef ADNS_JGAA_WIN32
  WSACleanup();
#endif /* WIN32 */

}