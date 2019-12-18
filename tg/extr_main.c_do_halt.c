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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  exit (int) ; 
 int exit_code ; 
 int /*<<< orphan*/  readline_disabled ; 
 int /*<<< orphan*/  rl_cleanup_after_signal () ; 
 int /*<<< orphan*/  rl_free_line_state () ; 
 scalar_t__ sfd ; 
 scalar_t__ unix_socket ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 scalar_t__ usfd ; 
 scalar_t__ write (int,char*,int) ; 

void do_halt (int error) {
  int retval;
  if (daemonize) {
    return;
  }

  if (!readline_disabled) {
    rl_free_line_state ();
    rl_cleanup_after_signal ();
  }

  if (write (1, "halt\n", 5) < 0) { 
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
 
  if (exit_code) {
    retval = exit_code;
  } else {
    retval = error ? EXIT_FAILURE : EXIT_SUCCESS;
  }

  exit (retval);
}