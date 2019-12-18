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
struct tgl_user {int /*<<< orphan*/  status; int /*<<< orphan*/  id; } ;
struct tgl_state {int dummy; } ;
struct in_ev {int dummy; } ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  binlog_read ; 
 scalar_t__ disable_output ; 
 int /*<<< orphan*/  enable_json ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_pack_user_status (struct tgl_user*) ; 
 int log_level ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,...) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 struct in_ev* notify_ev ; 
 int /*<<< orphan*/  print_user_name (struct in_ev*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  print_user_status (int /*<<< orphan*/ *,struct in_ev*) ; 

void user_status_upd (struct tgl_state *TLS, struct tgl_user *U) {
  if (disable_output && !notify_ev) { return; }
  if (!binlog_read) { return; }
  if (log_level < 3) { return; }
  struct in_ev *ev = notify_ev;
  mprint_start (ev);
  if (!enable_json)
  {
    mpush_color (ev, COLOR_YELLOW);
    mprintf (ev, "User ");
    print_user_name(ev, U->id, (void *) U);
    mprintf (ev, " ");
    print_user_status(&U->status, ev);
    mprintf (ev, "\n");
    mpop_color (ev);
  } else {
    #ifdef USE_JSON
      json_t *res = json_pack_user_status(U);
      char *s = json_dumps (res, 0);
      mprintf (ev, "%s\n", s);
      json_decref (res);
      free (s);
    #endif
  }
  mprint_end (ev);
}