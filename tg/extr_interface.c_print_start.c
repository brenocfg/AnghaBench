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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  deactivate_readline () ; 
 scalar_t__ in_readline ; 
 int prompt_was ; 
 scalar_t__ readline_active ; 
 scalar_t__ readline_disabled ; 

void print_start (void) {
  if (in_readline) { return; }
  if (readline_disabled) { return; }
  assert (!prompt_was);
  if (readline_active) {
    deactivate_readline ();
  }
  prompt_was = 1;
}