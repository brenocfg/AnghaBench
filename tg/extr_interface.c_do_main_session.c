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
struct in_ev {int /*<<< orphan*/  refcnt; } ;
struct command {int dummy; } ;
struct arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct in_ev*) ; 
 struct in_ev* notify_ev ; 

void do_main_session (struct command *command, int arg_num, struct arg args[], struct in_ev *ev) {
  if (notify_ev && !--notify_ev->refcnt) {
    free (notify_ev);
  }
  notify_ev = ev;
  if (ev) { ev->refcnt ++; }
}