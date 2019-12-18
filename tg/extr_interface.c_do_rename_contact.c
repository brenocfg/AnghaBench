#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ phone; } ;
struct TYPE_5__ {TYPE_1__ user; } ;
typedef  TYPE_2__ tgl_peer_t ;
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {scalar_t__ str; int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_success_gw (int /*<<< orphan*/ ,struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_user_list_gw ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  tgl_do_add_contact (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_ev*) ; 
 TYPE_2__* tgl_peer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_rename_contact (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 3);
  
  tgl_peer_t *P = tgl_peer_get (TLS, args[0].peer_id);
  if (P && P->user.phone) {
    if (ev) { ev->refcnt ++; }
    tgl_do_add_contact (TLS, P->user.phone, strlen (P->user.phone), args[1].str, strlen (args[1].str), args[2].str, strlen (args[2].str), 0, print_user_list_gw, ev);
  } else {
    if (ev) { ev->refcnt ++; }
    print_success_gw (TLS, ev, 0);
  }
}