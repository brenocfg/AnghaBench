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
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ in_readline ; 
 scalar_t__ prompt_was ; 
 int /*<<< orphan*/  reactivate_readline () ; 
 scalar_t__ readline_active ; 
 scalar_t__ readline_disabled ; 
 int /*<<< orphan*/  stdout ; 

void print_end (void) {
  if (in_readline) { return; }
  if (readline_disabled) { 
    fflush (stdout);
    return; 
  }
  assert (prompt_was);
  if (readline_active) {
    reactivate_readline ();
  }
  prompt_was = 0;
}