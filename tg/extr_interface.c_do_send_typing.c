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
typedef  enum tgl_typing_status { ____Placeholder_tgl_typing_status } tgl_typing_status ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int NOT_FOUND ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fail_interface (int /*<<< orphan*/ ,struct in_ev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_success_gw ; 
 int /*<<< orphan*/  tgl_do_send_typing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct in_ev*) ; 
 int tgl_typing_typing ; 

void do_send_typing (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 2);
  enum tgl_typing_status status = tgl_typing_typing; //de
  if (args[1].num != NOT_FOUND) {
    if (args[1].num > 0 && args[1].num > 10) {
      fail_interface (TLS, ev, ENOSYS, "illegal typing status");
      return;
    }
    status = (enum tgl_typing_status) args[1].num;  // if the status parameter is given, and is in range.
  }
  if (ev) { ev->refcnt ++; }
  tgl_do_send_typing (TLS, args[0].peer_id, status, print_success_gw, ev);
}