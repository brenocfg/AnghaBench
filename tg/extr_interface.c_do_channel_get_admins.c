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
struct arg {int num; int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int NOT_FOUND ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_user_list_gw ; 
 int /*<<< orphan*/  tgl_do_channel_get_members (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_channel_get_admins (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 3);
  if (ev) { ev->refcnt ++; }
  tgl_do_channel_get_members (TLS, args[0].peer_id, args[1].num == NOT_FOUND ? 100 : args[1].num, args[2].num == NOT_FOUND ? 0 : args[2].num, 1, print_user_list_gw, ev);
}