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
struct tgl_user {int /*<<< orphan*/  id; int /*<<< orphan*/  username; } ;
struct tgl_state {int dummy; } ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 unsigned int TGL_UPDATE_CREATED ; 
 unsigned int TGL_UPDATE_DELETED ; 
 struct tgl_state* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_read ; 
 scalar_t__ disable_output ; 
 int /*<<< orphan*/  enable_json ; 
 int /*<<< orphan*/  json_peer_update (struct in_ev*,void*,unsigned int) ; 
 int /*<<< orphan*/  lua_user_update (struct tgl_user*,unsigned int) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 struct in_ev* notify_ev ; 
 int /*<<< orphan*/  peer_update_username (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_peer_updates (struct in_ev*,unsigned int) ; 
 int /*<<< orphan*/  print_user_name (struct in_ev*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  py_user_update (struct tgl_user*,unsigned int) ; 

void user_update_gw (struct tgl_state *TLSR, struct tgl_user *U, unsigned flags) {
  assert (TLSR == TLS);
  #ifdef USE_LUA
    lua_user_update (U, flags);
  #endif
  #ifdef USE_PYTHON
    py_user_update (U, flags);
  #endif

  peer_update_username ((void *)U, U->username);
 
  if (disable_output && !notify_ev) { return; }
  if (!binlog_read) { return; }
  struct in_ev *ev = notify_ev;

  if (!(flags & TGL_UPDATE_CREATED)) {
    mprint_start (ev);
    if (!enable_json) {
      mpush_color (ev, COLOR_YELLOW);
      mprintf (ev, "User ");
      print_user_name (ev, U->id, (void *)U);
      if (!(flags & TGL_UPDATE_DELETED)) {
        mprintf (ev, " updated");
        print_peer_updates (ev, flags);
      } else {
        mprintf (ev, " deleted");
      }
      mprintf (ev, "\n");
      mpop_color (ev);
    } else {
      json_peer_update (ev, (void *)U, flags);
    }
    mprint_end (ev);
  }
}