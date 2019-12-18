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
struct TYPE_4__ {int /*<<< orphan*/  title; } ;
struct TYPE_5__ {TYPE_1__ channel; } ;
typedef  TYPE_2__ tgl_peer_t ;
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CYAN ; 
 scalar_t__ TGL_PEER_CHANNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 scalar_t__ permanent_peer_id_mode ; 
 int /*<<< orphan*/  print_peer_permanent_name (struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgl_get_peer_id (int /*<<< orphan*/ ) ; 
 scalar_t__ tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 scalar_t__ use_ids ; 

void print_channel_name (struct in_ev *ev, tgl_peer_id_t id, tgl_peer_t *C) {
  assert (tgl_get_peer_type (id) == TGL_PEER_CHANNEL);
  mpush_color (ev, COLOR_CYAN);
  if (permanent_peer_id_mode) {
    print_peer_permanent_name (ev, id);
    mpop_color (ev);
    return;
  }
  if (!C || use_ids) {
    mprintf (ev, "channel#%d", tgl_get_peer_id (id));
  } else {
    mprintf (ev, "%s", C->channel.title);
  }
  mpop_color (ev);
}