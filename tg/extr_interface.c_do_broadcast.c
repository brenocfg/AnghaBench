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
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int /*<<< orphan*/  str; int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int disable_msg_preview ; 
 int do_html ; 
 int /*<<< orphan*/  print_msg_list_success_gw ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_do_send_broadcast (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_broadcast (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num >= 1 && arg_num <= 1000);
  static tgl_peer_id_t ids[1000];
  int i;
  for (i = 0; i < arg_num - 1; i++) {
    ids[i] = args[i].peer_id;
  }  
  if (ev) { ev->refcnt ++; }
  tgl_do_send_broadcast (TLS, arg_num - 1, ids, args[arg_num - 1].str, strlen (args[arg_num - 1].str), disable_msg_preview | do_html, print_msg_list_success_gw, ev);
}