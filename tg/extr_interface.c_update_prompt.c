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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_default_prompt () ; 
 int /*<<< orphan*/  print_end () ; 
 int /*<<< orphan*/  print_start () ; 
 scalar_t__ read_one_string ; 
 scalar_t__ readline_active ; 
 scalar_t__ readline_disabled ; 
 int /*<<< orphan*/  rl_redisplay () ; 
 int /*<<< orphan*/  set_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void update_prompt (void) {
  if (readline_disabled) {
    fflush (stdout);
    return;
  }
  if (read_one_string) { return; }
  print_start ();
  set_prompt (get_default_prompt ());
  if (readline_active) {
    rl_redisplay ();
  }
  print_end ();
}