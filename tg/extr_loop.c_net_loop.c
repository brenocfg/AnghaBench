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
struct TYPE_3__ {int /*<<< orphan*/  active_queries; int /*<<< orphan*/  ev_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOOP_ONCE ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 scalar_t__ E_DEBUG ; 
 TYPE_1__* TLS ; 
 scalar_t__ delete_stdin_event ; 
 int /*<<< orphan*/  do_halt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_add (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_free (scalar_t__) ; 
 scalar_t__ event_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logprintf (char*) ; 
 int /*<<< orphan*/  lua_do_all () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  py_do_all () ; 
 scalar_t__ safe_quit ; 
 scalar_t__ sigterm_cnt ; 
 int /*<<< orphan*/  stdin_read_callback ; 
 scalar_t__ term_ev ; 
 int /*<<< orphan*/  tgl_do_lookup_state (TYPE_1__*) ; 
 int time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_prompt () ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_state_file () ; 

void net_loop (void) {
  delete_stdin_event = 0;
  if (verbosity >= E_DEBUG) {
    logprintf ("Starting netloop\n");
  }
  term_ev = event_new (TLS->ev_base, 0, EV_READ | EV_PERSIST, stdin_read_callback, 0);
  event_add (term_ev, 0);
  
  int last_get_state = time (0);
  while (1) {
    event_base_loop (TLS->ev_base, EVLOOP_ONCE);

    if (term_ev && delete_stdin_event) {
      logprintf ("delete stdin\n");
      event_free (term_ev);
      term_ev = 0;
    }

    #ifdef USE_LUA
      lua_do_all ();
    #endif
    
    #ifdef USE_PYTHON
      py_do_all ();
    #endif

    if (safe_quit && !TLS->active_queries) {
      printf ("All done. Exit\n");
      do_halt (0);
      safe_quit = 0;
    }
    if (sigterm_cnt > 0) {
      do_halt (0);
    }
    if (time (0) - last_get_state > 3600) {
      tgl_do_lookup_state (TLS);
      last_get_state = time (0);
    }
    
    write_state_file ();
    update_prompt ();
    
/*    if (unknown_user_list_pos) {
      int i;
      for (i = 0; i < unknown_user_list_pos; i++) {
        tgl_do_get_user_info (TLS, TGL_MK_USER (unknown_user_list[i]), 0, 0, 0);
      }
      unknown_user_list_pos = 0;
    }   */
  }

  if (term_ev) {
    event_free (term_ev);
    term_ev = 0;
  }
  
  if (verbosity >= E_DEBUG) {
    logprintf ("End of netloop\n");
  }
}