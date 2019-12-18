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

/* Variables and functions */
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_cnt ; 
 int /*<<< orphan*/  termination_signal_handler ; 
 scalar_t__ write (int,char*,int) ; 

void sig_term_handler (int signum __attribute__ ((unused))) {
  signal (signum, termination_signal_handler);
  //set_terminal_attributes ();
  if (write (1, "SIGTERM/SIGINT received\n", 25) < 0) { 
    // Sad thing
  }
  //if (TLS && TLS->ev_base) {
  //  event_base_loopbreak (TLS->ev_base);
  //}
  sigterm_cnt ++;
}