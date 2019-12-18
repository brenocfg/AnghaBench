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
struct TYPE_3__ {int /*<<< orphan*/  encr_chat; } ;
typedef  TYPE_1__ tgl_peer_t ;
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int /*<<< orphan*/  peer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  print_encr_chat_success_gw ; 
 int /*<<< orphan*/  print_success_gw (int /*<<< orphan*/ ,struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_do_accept_encr_chat_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in_ev*) ; 
 TYPE_1__* tgl_peer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_accept_secret_chat (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 1);
  if (ev) { ev->refcnt ++; }

  tgl_peer_t *P = tgl_peer_get (TLS, args[0].peer_id);
  if (P) {
    tgl_do_accept_encr_chat_request (TLS, &P->encr_chat, print_encr_chat_success_gw, ev);
  } else {
    print_success_gw (TLS, ev, 0);
  }
}