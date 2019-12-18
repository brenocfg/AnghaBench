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
typedef  int /*<<< orphan*/  tgl_message_id_t ;
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int /*<<< orphan*/  peer_id; int /*<<< orphan*/  msg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_msg_list_success_gw ; 
 int /*<<< orphan*/  tgl_do_forward_messages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_fwd (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num >= 2);
  if (ev) { ev->refcnt ++; }
  assert (arg_num <= 1000);
  //if (arg_num == 2) {
  //  tgl_do_forward_message (TLS, args[0].P->id, &args[1].msg_id, 0, print_msg_success_gw, ev);
  //} else {
    static tgl_message_id_t *list[1000];
    int i;
    for (i = 0; i < arg_num - 1; i++) {
      list[i] = &args[i + 1].msg_id;
    }
    tgl_do_forward_messages (TLS, args[0].peer_id, arg_num - 1, (void *)list, 0, print_msg_list_success_gw, ev);
  //}
}