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
struct arg {int num; int /*<<< orphan*/  str; int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int NOT_FOUND ; 
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_msg_list_gw ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_do_msg_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_ev*) ; 

void do_search (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 6);
  int limit;
  if (args[1].num != NOT_FOUND) {
    limit = args[1].num; 
  } else {
    limit = 40;
  }
  int from;
  if (args[2].num != NOT_FOUND) {
    from = args[2].num; 
  } else {
    from = 0;
  }
  int to;
  if (args[3].num != NOT_FOUND) {
    to = args[3].num; 
  } else {
    to = 0;
  }
  int offset;
  if (args[4].num != NOT_FOUND) {
    offset = args[4].num; 
  } else {
    offset = 0;
  }
  if (ev) { ev->refcnt ++; }
  tgl_do_msg_search (TLS, args[0].peer_id, from, to, limit, offset, args[5].str, strlen (args[5].str), print_msg_list_gw, ev);
}