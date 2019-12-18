#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  h; int /*<<< orphan*/  msecs; } ;
struct TYPE_10__ {TYPE_7__* netif; int /*<<< orphan*/  p; } ;
struct TYPE_14__ {TYPE_5__ cb; TYPE_4__ tmo; TYPE_3__* netifapimsg; TYPE_2__ inp; TYPE_1__* apimsg; } ;
struct tcpip_msg {int type; TYPE_6__ msg; } ;
struct TYPE_15__ {int flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_TCPIP_CORE () ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWIP_TCPIP_THREAD_ALIVE () ; 
 int /*<<< orphan*/  LWIP_UNUSED_ARG (void*) ; 
 int /*<<< orphan*/  MEMP_TCPIP_MSG_API ; 
 int /*<<< orphan*/  MEMP_TCPIP_MSG_INPKT ; 
 int NETIF_FLAG_ETHARP ; 
 int NETIF_FLAG_ETHERNET ; 
 int /*<<< orphan*/  TCPIP_DEBUG ; 
#define  TCPIP_MSG_API 134 
#define  TCPIP_MSG_CALLBACK 133 
#define  TCPIP_MSG_CALLBACK_STATIC 132 
#define  TCPIP_MSG_INPKT 131 
#define  TCPIP_MSG_NETIFAPI 130 
#define  TCPIP_MSG_TIMEOUT 129 
#define  TCPIP_MSG_UNTIMEOUT 128 
 int /*<<< orphan*/  UNLOCK_TCPIP_CORE () ; 
 int /*<<< orphan*/  ethernet_input (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ip_input (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  mbox ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct tcpip_msg*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_timeouts_mbox_fetch (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  sys_untimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpip_init_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpip_init_done_arg ; 

__attribute__((used)) static void
tcpip_thread(void *arg)
{
  struct tcpip_msg *msg;
  LWIP_UNUSED_ARG(arg);

  if (tcpip_init_done != NULL) {
    tcpip_init_done(tcpip_init_done_arg);
  }

  LOCK_TCPIP_CORE();
  while (1) {                          /* MAIN Loop */
    UNLOCK_TCPIP_CORE();
    LWIP_TCPIP_THREAD_ALIVE();
    /* wait for a message, timeouts are processed while waiting */
    sys_timeouts_mbox_fetch(&mbox, (void **)&msg);
    LOCK_TCPIP_CORE();
    switch (msg->type) {
#if LWIP_NETCONN
    case TCPIP_MSG_API:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: API message %p\n", (void *)msg));
      msg->msg.apimsg->function(&(msg->msg.apimsg->msg));
      break;
#endif /* LWIP_NETCONN */

#if !LWIP_TCPIP_CORE_LOCKING_INPUT
    case TCPIP_MSG_INPKT:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: PACKET %p\n", (void *)msg));
#if LWIP_ETHERNET
      if (msg->msg.inp.netif->flags & (NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET)) {
        ethernet_input(msg->msg.inp.p, msg->msg.inp.netif);
      } else
#endif /* LWIP_ETHERNET */
      {
        ip_input(msg->msg.inp.p, msg->msg.inp.netif);
      }
      memp_free(MEMP_TCPIP_MSG_INPKT, msg);
      break;
#endif /* LWIP_TCPIP_CORE_LOCKING_INPUT */

#if LWIP_NETIF_API
    case TCPIP_MSG_NETIFAPI:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: Netif API message %p\n", (void *)msg));
      msg->msg.netifapimsg->function(&(msg->msg.netifapimsg->msg));
      break;
#endif /* LWIP_NETIF_API */

#if LWIP_TCPIP_TIMEOUT
    case TCPIP_MSG_TIMEOUT:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: TIMEOUT %p\n", (void *)msg));
      sys_timeout(msg->msg.tmo.msecs, msg->msg.tmo.h, msg->msg.tmo.arg);
      memp_free(MEMP_TCPIP_MSG_API, msg);
      break;
    case TCPIP_MSG_UNTIMEOUT:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: UNTIMEOUT %p\n", (void *)msg));
      sys_untimeout(msg->msg.tmo.h, msg->msg.tmo.arg);
      memp_free(MEMP_TCPIP_MSG_API, msg);
      break;
#endif /* LWIP_TCPIP_TIMEOUT */

    case TCPIP_MSG_CALLBACK:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: CALLBACK %p\n", (void *)msg));
      msg->msg.cb.function(msg->msg.cb.ctx);
      memp_free(MEMP_TCPIP_MSG_API, msg);
      break;

    case TCPIP_MSG_CALLBACK_STATIC:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: CALLBACK_STATIC %p\n", (void *)msg));
      msg->msg.cb.function(msg->msg.cb.ctx);
      break;

    default:
      LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_thread: invalid message: %d\n", msg->type));
      LWIP_ASSERT("tcpip_thread: invalid message", 0);
      break;
    }
  }
}