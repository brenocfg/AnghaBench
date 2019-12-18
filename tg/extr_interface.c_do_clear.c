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
struct in_ev {int dummy; } ;
struct event_base {int dummy; } ;
struct command {int dummy; } ;
struct arg {int dummy; } ;
struct TYPE_3__ {struct event_base* ev_base; } ;

/* Variables and functions */
 TYPE_1__* TLS ; 
 scalar_t__ auth_file_name ; 
 scalar_t__ binlog_file_name ; 
 int /*<<< orphan*/  clear_history () ; 
 scalar_t__ config_filename ; 
 int /*<<< orphan*/  default_username ; 
 int /*<<< orphan*/  do_halt (int /*<<< orphan*/ ) ; 
 scalar_t__ downloads_directory ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ home_directory ; 
 int /*<<< orphan*/  logprintf (char*,...) ; 
 scalar_t__ lua_file ; 
 scalar_t__ python_file ; 
 scalar_t__ secret_chat_file_name ; 
 scalar_t__ state_file_name ; 
 int /*<<< orphan*/  term_ev ; 
 int /*<<< orphan*/  tfree_str (scalar_t__) ; 
 int /*<<< orphan*/  tgl_free_all (TYPE_1__*) ; 
 int /*<<< orphan*/  tgl_get_allocated_bytes () ; 

void do_clear (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  logprintf ("Do_clear\n");
  free (default_username);
  tfree_str (config_filename);
  //free (prefix);
  tfree_str (auth_file_name);
  tfree_str (state_file_name);
  tfree_str (secret_chat_file_name);
  tfree_str (downloads_directory);
  //tfree_str (config_directory);
  tfree_str (binlog_file_name);
  tfree_str (lua_file);
  tfree_str (python_file);
  if (home_directory) {
    tfree_str (home_directory);
  }
  clear_history ();
  event_free (term_ev);
  struct event_base *ev_base = TLS->ev_base;
  tgl_free_all (TLS);
  event_base_free (ev_base);
  logprintf ("Bytes left allocated: %lld\n", tgl_get_allocated_bytes ());
  do_halt (0);
}