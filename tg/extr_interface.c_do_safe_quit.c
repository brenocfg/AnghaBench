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
struct in_ev {int /*<<< orphan*/  bev; } ;
struct command {int dummy; } ;
struct arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_EVENT_EOF ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  event_incoming (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_ev*) ; 
 int safe_quit ; 

void do_safe_quit (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  if (daemonize) {
    event_incoming (ev->bev, BEV_EVENT_EOF, ev);
  }
  safe_quit = 1;
}