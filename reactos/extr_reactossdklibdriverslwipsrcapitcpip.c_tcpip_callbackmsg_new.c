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
typedef  int /*<<< orphan*/  tcpip_callback_fn ;
struct TYPE_3__ {void* ctx; int /*<<< orphan*/  function; } ;
struct TYPE_4__ {TYPE_1__ cb; } ;
struct tcpip_msg {TYPE_2__ msg; int /*<<< orphan*/  type; } ;
struct tcpip_callback_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMP_TCPIP_MSG_API ; 
 int /*<<< orphan*/  TCPIP_MSG_CALLBACK_STATIC ; 
 scalar_t__ memp_malloc (int /*<<< orphan*/ ) ; 

struct tcpip_callback_msg* tcpip_callbackmsg_new(tcpip_callback_fn function, void *ctx)
{
  struct tcpip_msg *msg = (struct tcpip_msg *)memp_malloc(MEMP_TCPIP_MSG_API);
  if (msg == NULL) {
    return NULL;
  }
  msg->type = TCPIP_MSG_CALLBACK_STATIC;
  msg->msg.cb.function = function;
  msg->msg.cb.ctx = ctx;
  return (struct tcpip_callback_msg*)msg;
}