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
struct arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tgl_print_stat (int /*<<< orphan*/ ,char*,int) ; 

void do_stats (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (!arg_num);
  static char stat_buf[1 << 15];
  tgl_print_stat (TLS, stat_buf, (1 << 15) - 1);
  if (ev) { mprint_start (ev); }
  mprintf (ev, "%s\n", stat_buf);
  if (ev) { mprint_end (ev); }
  if (!ev) {
    fflush (stdout);
  }
}