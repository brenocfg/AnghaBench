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
struct arg {int /*<<< orphan*/ * str; int /*<<< orphan*/  msg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_msg_success_gw ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tgl_do_reply_document (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,struct in_ev*) ; 

void _do_reply_file (struct command *command, int arg_num, struct arg args[], struct in_ev *ev, unsigned long long flags) {
  assert (arg_num >= 2);
  if (ev) { ev->refcnt ++; }
  tgl_do_reply_document (TLS, &args[0].msg_id, args[1].str, arg_num == 2 ? NULL : args[2].str, arg_num == 2 ? 0 : strlen (args[2].str), flags, print_msg_success_gw, ev);
}