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
struct tgl_state {int dummy; } ;
struct tgl_message {int /*<<< orphan*/  to_id; } ;
struct in_ev {int dummy; } ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 scalar_t__ TGL_PEER_ENCR_CHAT ; 
 struct tgl_state* TLS ; 
 scalar_t__ alert_sound ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_read ; 
 scalar_t__ disable_output ; 
 int /*<<< orphan*/  enable_json ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_pack_message (struct tgl_message*) ; 
 int /*<<< orphan*/  lua_new_msg (struct tgl_message*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,char*) ; 
 struct in_ev* notify_ev ; 
 int /*<<< orphan*/  play_sound () ; 
 int /*<<< orphan*/  print_message (struct in_ev*,struct tgl_message*) ; 
 int /*<<< orphan*/  py_new_msg (struct tgl_message*) ; 
 scalar_t__ tgl_get_peer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_secret_chat_file () ; 

void print_message_gw (struct tgl_state *TLSR, struct tgl_message *M) {
  assert (TLSR == TLS);
  #ifdef USE_LUA
    lua_new_msg (M);
  #endif
  #ifdef USE_PYTHON
    py_new_msg (M);
  #endif
  if (!binlog_read) { return; }
  if (tgl_get_peer_type (M->to_id) == TGL_PEER_ENCR_CHAT) { 
    write_secret_chat_file ();
  }
  if (alert_sound) {
    play_sound ();
  }
  if (disable_output && !notify_ev) { return; }
  struct in_ev *ev = notify_ev;
  mprint_start (ev);
  if (!enable_json) {
    print_message (ev, M);
  } else {
    #ifdef USE_JSON
      json_t *res = json_pack_message (M);
      char *s = json_dumps (res, 0);
      mprintf (ev, "%s\n", s);
      json_decref (res);
      free (s);
    #endif
  }
  mprint_end (ev);
}