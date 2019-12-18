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
struct TYPE_3__ {int /*<<< orphan*/  print_name; } ;
typedef  TYPE_1__ tgl_peer_t ;
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_MAGENTA ; 
 scalar_t__ TGL_PEER_ENCR_CHAT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 scalar_t__ permanent_peer_id_mode ; 
 int /*<<< orphan*/  print_peer_permanent_name (struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_get_peer_id (int /*<<< orphan*/ ) ; 
 scalar_t__ tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 scalar_t__ use_ids ; 

void print_encr_chat_name (struct in_ev *ev, tgl_peer_id_t id, tgl_peer_t *C) {
  assert (tgl_get_peer_type (id) == TGL_PEER_ENCR_CHAT);
  mpush_color (ev, COLOR_MAGENTA);
  if (permanent_peer_id_mode) {
    print_peer_permanent_name (ev, id);
    mpop_color (ev);
    return;
  }
  if (!C || use_ids) {
    mprintf (ev, "encr_chat#%d", tgl_get_peer_id (id));
  } else {
    mprintf (ev, "%s", C->print_name);
  }
  mpop_color (ev);
}