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
struct TYPE_4__ {int /*<<< orphan*/  last_name; int /*<<< orphan*/  first_name; } ;
struct TYPE_5__ {int flags; TYPE_1__ user; } ;
typedef  TYPE_2__ tgl_peer_t ;
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_RED ; 
 int /*<<< orphan*/  COLOR_REDB ; 
 int TGLUF_CONTACT ; 
 int TGLUF_CREATED ; 
 int TGLUF_DELETED ; 
 int TGLUF_SELF ; 
 scalar_t__ TGL_PEER_USER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 scalar_t__ permanent_peer_id_mode ; 
 int /*<<< orphan*/  print_peer_permanent_name (struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ tgl_get_peer_id (int /*<<< orphan*/ ) ; 
 scalar_t__ tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 scalar_t__* unknown_user_list ; 
 int unknown_user_list_pos ; 
 scalar_t__ use_ids ; 

void print_user_name (struct in_ev *ev, tgl_peer_id_t id, tgl_peer_t *U) {
  assert (tgl_get_peer_type (id) == TGL_PEER_USER);
  mpush_color (ev, COLOR_RED);
  if (permanent_peer_id_mode) {
    print_peer_permanent_name (ev, id);
    mpop_color (ev);
    return;
  }
  if (!U) {
    mprintf (ev, "user#%d", tgl_get_peer_id (id));
    int i;
    int ok = 1;
    for (i = 0; i < unknown_user_list_pos; i++) {
      if (unknown_user_list[i] == tgl_get_peer_id (id)) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      assert (unknown_user_list_pos < 1000);
      unknown_user_list[unknown_user_list_pos ++] = tgl_get_peer_id (id);
    }
  } else {
    if (U->flags & (TGLUF_SELF | TGLUF_CONTACT)) {
      mpush_color (ev, COLOR_REDB);
    }
    if ((U->flags & TGLUF_DELETED)) {
      mprintf (ev, "deleted user#%d", tgl_get_peer_id (id));
    } else if (!(U->flags & TGLUF_CREATED)) {
      mprintf (ev, "user#%d", tgl_get_peer_id (id));
    } else if (use_ids) {
      mprintf (ev, "user#%d", tgl_get_peer_id (id));
    } else if (!U->user.first_name || !strlen (U->user.first_name)) {
      mprintf (ev, "%s", U->user.last_name);
    } else if (!U->user.last_name || !strlen (U->user.last_name)) {
      mprintf (ev, "%s", U->user.first_name);
    } else {
      mprintf (ev, "%s %s", U->user.first_name, U->user.last_name); 
    }
    if (U->flags & (TGLUF_SELF | TGLUF_CONTACT)) {
      mpop_color (ev);
    }
  }
  mpop_color (ev);
}