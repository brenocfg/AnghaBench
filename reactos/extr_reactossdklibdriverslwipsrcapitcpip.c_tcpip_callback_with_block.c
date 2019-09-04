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
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  tcpip_callback_fn ;
struct TYPE_4__ {void* ctx; int /*<<< orphan*/  function; } ;
struct TYPE_3__ {TYPE_2__ cb; } ;
struct tcpip_msg {TYPE_1__ msg; int /*<<< orphan*/  type; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_MEM ; 
 scalar_t__ ERR_OK ; 
 scalar_t__ ERR_VAL ; 
 int /*<<< orphan*/  MEMP_TCPIP_MSG_API ; 
 int /*<<< orphan*/  TCPIP_MSG_CALLBACK ; 
 int /*<<< orphan*/  mbox ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct tcpip_msg*) ; 
 scalar_t__ memp_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_mbox_post (int /*<<< orphan*/ *,struct tcpip_msg*) ; 
 scalar_t__ sys_mbox_trypost (int /*<<< orphan*/ *,struct tcpip_msg*) ; 
 scalar_t__ sys_mbox_valid (int /*<<< orphan*/ *) ; 

err_t
tcpip_callback_with_block(tcpip_callback_fn function, void *ctx, u8_t block)
{
  struct tcpip_msg *msg;

  if (sys_mbox_valid(&mbox)) {
    msg = (struct tcpip_msg *)memp_malloc(MEMP_TCPIP_MSG_API);
    if (msg == NULL) {
      return ERR_MEM;
    }

    msg->type = TCPIP_MSG_CALLBACK;
    msg->msg.cb.function = function;
    msg->msg.cb.ctx = ctx;
    if (block) {
      sys_mbox_post(&mbox, msg);
    } else {
      if (sys_mbox_trypost(&mbox, msg) != ERR_OK) {
        memp_free(MEMP_TCPIP_MSG_API, msg);
        return ERR_MEM;
      }
    }
    return ERR_OK;
  }
  return ERR_VAL;
}