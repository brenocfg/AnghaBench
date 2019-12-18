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
struct in_ev {int dummy; } ;
struct command {int dummy; } ;
struct arg {int num; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int alert_sound ; 
 int log_level ; 
 int msg_num_mode ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tgl_set_verbosity (int /*<<< orphan*/ ,int) ; 

void do_set (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  int num = args[1].num;
  if (!strcmp (args[0].str, "debug_verbosity")) {
    tgl_set_verbosity (TLS, num); 
  } else if (!strcmp (args[0].str, "log_level")) {
    log_level = num;
  } else if (!strcmp (args[0].str, "msg_num")) {
    msg_num_mode = num;
  } else if (!strcmp (args[0].str, "alert")) {
    alert_sound = num;
  }
}