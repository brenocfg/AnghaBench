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
struct arg {scalar_t__ num; int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 scalar_t__ NOT_FOUND ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  offline_mode ; 
 int /*<<< orphan*/  print_msg_list_history_gw ; 
 int /*<<< orphan*/  tgl_do_get_history (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_history (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 3);
  if (ev) { ev->refcnt ++; }
  tgl_do_get_history (TLS, args[0].peer_id, args[2].num != NOT_FOUND ? args[2].num : 0, args[1].num != NOT_FOUND ? args[1].num : 40, offline_mode, print_msg_list_history_gw, ev);
}