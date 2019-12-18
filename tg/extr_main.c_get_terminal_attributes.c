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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  term_in ; 
 int /*<<< orphan*/  term_out ; 
 int term_set_in ; 
 int term_set_out ; 

void get_terminal_attributes (void) {
  if (tcgetattr (STDIN_FILENO, &term_in) < 0) {
  } else {
    term_set_in = 1;
  }
  if (tcgetattr (STDOUT_FILENO, &term_out) < 0) {
  } else {
    term_set_out = 1;
  }
}