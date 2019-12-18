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
typedef  int /*<<< orphan*/  tgl_peer_t ;
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct in_ev {int dummy; } ;

/* Variables and functions */
#define  TGL_PEER_CHANNEL 131 
#define  TGL_PEER_CHAT 130 
#define  TGL_PEER_ENCR_CHAT 129 
#define  TGL_PEER_USER 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_channel_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_chat_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_encr_chat_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_user_name (struct in_ev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tgl_get_peer_type (int /*<<< orphan*/ ) ; 

void print_peer_name  (struct in_ev *ev, tgl_peer_id_t id, tgl_peer_t *C) {
  switch (tgl_get_peer_type (id)) {
  case TGL_PEER_USER:
    print_user_name (ev, id, C);
    return;
  case TGL_PEER_CHAT:
    print_chat_name (ev, id, C);
    return;
  case TGL_PEER_CHANNEL:
    print_channel_name (ev, id, C);
    return;
  case TGL_PEER_ENCR_CHAT:
    print_encr_chat_name (ev, id, C);
    return;
  default:
    assert (0);
  }
}