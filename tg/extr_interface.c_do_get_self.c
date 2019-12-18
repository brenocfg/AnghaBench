#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  our_id; } ;

/* Variables and functions */
 TYPE_1__* TLS ; 
 int /*<<< orphan*/  print_user_info_gw ; 
 int /*<<< orphan*/  tgl_do_get_user_info (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_get_self(struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  if (ev) { ev->refcnt ++; }
  tgl_do_get_user_info (TLS, TLS->our_id, 0, print_user_info_gw, ev);
}