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
struct tgl_state {int dummy; } ;
struct tgl_message {int /*<<< orphan*/  server_id; int /*<<< orphan*/  from_id; int /*<<< orphan*/  to_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  our_id; } ;

/* Variables and functions */
 TYPE_1__* TLS ; 
 int /*<<< orphan*/  print_msg_list_gw (struct tgl_state*,void*,int,int,struct tgl_message**) ; 
 scalar_t__ tgl_cmp_peer_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_do_messages_mark_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void print_msg_list_history_gw (struct tgl_state *TLSR, void *extra, int success, int num, struct tgl_message *ML[]) {
  print_msg_list_gw (TLSR, extra, success, num, ML);
  if (num > 0) {
    if (tgl_cmp_peer_id (ML[0]->to_id, TLS->our_id)) {
      tgl_do_messages_mark_read (TLS, ML[0]->to_id, ML[0]->server_id, 0, NULL, NULL);
    } else {
      tgl_do_messages_mark_read (TLS, ML[0]->from_id, ML[0]->server_id, 0, NULL, NULL);
    }
  }
}