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
struct tl_ds_reply_markup {int dummy; } ;
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG2STR (int) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int TGL_SEND_MSG_FLAG_REPLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  TYPE_TO_PARAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_packet () ; 
 int disable_msg_preview ; 
 int do_html ; 
 int /*<<< orphan*/  fail_interface (int /*<<< orphan*/ ,struct in_ev*,int /*<<< orphan*/ ,char*) ; 
 struct tl_ds_reply_markup* fetch_ds_type_reply_markup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ds_type_reply_markup (struct tl_ds_reply_markup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_end ; 
 int /*<<< orphan*/  in_ptr ; 
 int /*<<< orphan*/  packet_buffer ; 
 int /*<<< orphan*/  packet_ptr ; 
 int /*<<< orphan*/  print_msg_success_gw ; 
 int /*<<< orphan*/  reply_id ; 
 int /*<<< orphan*/  reply_markup ; 
 int /*<<< orphan*/  tgl_do_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct tl_ds_reply_markup*,int /*<<< orphan*/ ,struct in_ev*) ; 
 scalar_t__ tglf_store_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_msg_kbd (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 3);
  if (ev) { ev->refcnt ++; }

  clear_packet ();  
  if (tglf_store_type (TLS, ARG2STR(1), TYPE_TO_PARAM (reply_markup)) < 0) {
    fail_interface (TLS, ev, ENOSYS, "can not parse reply markup");    
    return;
  }
  in_ptr = packet_buffer;
  in_end = packet_ptr;

  struct tl_ds_reply_markup *DS_RM = fetch_ds_type_reply_markup (TYPE_TO_PARAM (reply_markup));
  assert (DS_RM);

  tgl_do_send_message (TLS, args[0].peer_id, ARG2STR(2), TGL_SEND_MSG_FLAG_REPLY(reply_id) | disable_msg_preview | do_html, DS_RM, print_msg_success_gw, ev);

  free_ds_type_reply_markup (DS_RM, TYPE_TO_PARAM (reply_markup));
}