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
struct command {int /*<<< orphan*/  desc; scalar_t__ name; } ;
struct arg {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  assert (int) ; 
 struct command* commands ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,scalar_t__) ; 

void do_help (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (arg_num == 1);
  if (ev) { mprint_start (ev); }
  int total = 0;
  mpush_color (ev, COLOR_YELLOW);
  struct command *cmd = commands;
  while (cmd->name) {
    if (!args[0].str || !strcmp (args[0].str, cmd->name)) {
      mprintf (ev, "%s\n", cmd->desc);
      total ++;
    }
    cmd ++;
  }
  if (!total) {
    assert (arg_num == 1);
    mprintf (ev, "Unknown command '%s'\n", args[0].str);
  }
  mpop_color (ev);
  if (ev) { mprint_end (ev); }
  if (!ev) {
    fflush (stdout);
  }
}