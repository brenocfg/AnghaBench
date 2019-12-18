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
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  TELEGRAM_CLI_VERSION ; 
 int /*<<< orphan*/  TGL_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpop_color (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,...) ; 
 int /*<<< orphan*/  mpush_color (struct in_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void do_version (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  assert (!arg_num);
  if (ev) { mprint_start (ev); }
  mpush_color (ev, COLOR_YELLOW);
  mprintf (ev, "Telegram-cli version %s (uses tgl version %s)\n", TELEGRAM_CLI_VERSION, TGL_VERSION);
  #ifdef TGL_AVOID_OPENSSL 
    mprintf (ev, "uses libgcrypt for encryption\n");
  #else
    mprintf (ev, "uses libopenssl for encryption\n");
  #endif
  mpop_color (ev);
  if (ev) { mprint_end (ev); }
  if (!ev) {
    fflush (stdout);
  }

}