#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG2STR (int) ; 
 int /*<<< orphan*/  E_DEBUG ; 
 int TGLMF_POST_AS_CHANNEL ; 
 int TGL_SEND_MSG_FLAG_REPLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int disable_msg_preview ; 
 int do_html ; 
 int /*<<< orphan*/  print_msg_success_gw ; 
 int /*<<< orphan*/  reply_id ; 
 int /*<<< orphan*/  tgl_do_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in_ev*) ; 
 int /*<<< orphan*/  vlogprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

void do_post (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 2);
  if (ev) { ev->refcnt ++; }
  vlogprintf (E_DEBUG, "reply_id=%d, disable=%d\n", reply_id, disable_msg_preview);
  tgl_do_send_message (TLS, args[0].peer_id, ARG2STR(1), TGL_SEND_MSG_FLAG_REPLY(reply_id) | disable_msg_preview | TGLMF_POST_AS_CHANNEL | do_html, NULL, print_msg_success_gw, ev);
}