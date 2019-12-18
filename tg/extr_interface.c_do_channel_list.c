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
struct arg {scalar_t__ num; } ;

/* Variables and functions */
 scalar_t__ NOT_FOUND ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_dialog_list_gw ; 
 int /*<<< orphan*/  tgl_do_get_channels_dialog_list (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_channel_list (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num <= 2);
  if (ev) { ev->refcnt ++; }
  tgl_do_get_channels_dialog_list (TLS, args[0].num != NOT_FOUND ? args[0].num : 100, args[1].num != NOT_FOUND ? args[1].num : 0, print_dialog_list_gw, ev);
}