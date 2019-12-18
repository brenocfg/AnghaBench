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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ tgl_peer_t ;
struct tgl_state {int dummy; } ;

/* Variables and functions */
#define  TGL_PEER_CHANNEL 130 
#define  TGL_PEER_CHAT 129 
#define  TGL_PEER_USER 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_channel_gw (struct tgl_state*,void*,int,void*) ; 
 int /*<<< orphan*/  print_chat_gw (struct tgl_state*,void*,int,void*) ; 
 int /*<<< orphan*/  print_user_gw (struct tgl_state*,void*,int,void*) ; 
 int tgl_get_peer_type (int /*<<< orphan*/ ) ; 

void print_peer_gw (struct tgl_state *TLSR, void *extra, int success, tgl_peer_t *U) {
  if (!success) { 
    print_user_gw (TLSR, extra, success, (void *)U);
    return;
  }
  switch (tgl_get_peer_type (U->id)) {
  case TGL_PEER_USER:
    print_user_gw (TLSR, extra, success, (void *)U);
    break;
  case TGL_PEER_CHAT:
    print_chat_gw (TLSR, extra, success, (void *)U);
    break;
  case TGL_PEER_CHANNEL:
    print_channel_gw (TLSR, extra, success, (void *)U);
    break;
  default:
    assert (0);
  }
}