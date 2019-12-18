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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_backtrace () ; 
 int /*<<< orphan*/  readline_disabled ; 
 int /*<<< orphan*/  rl_cleanup_after_signal () ; 
 int /*<<< orphan*/  rl_free_line_state () ; 
 scalar_t__ sfd ; 
 scalar_t__ unix_socket ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 scalar_t__ usfd ; 
 scalar_t__ write (int,char*,int) ; 

void termination_signal_handler (int signum) {
  if (!readline_disabled) {
    rl_free_line_state ();
    rl_cleanup_after_signal ();
  }
  
  if (write (1, "SIGNAL received\n", 18) < 0) { 
    // Sad thing
  }
 
  if (unix_socket) {
    unlink (unix_socket);
  }
  
  if (usfd > 0) {
    close (usfd);
  }
  if (sfd > 0) {
    close (sfd);
  }
  print_backtrace ();
  
  exit (EXIT_FAILURE);
}