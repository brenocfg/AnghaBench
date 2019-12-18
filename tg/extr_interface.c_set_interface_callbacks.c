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
 int /*<<< orphan*/  command_generator ; 
 int /*<<< orphan*/  get_default_prompt () ; 
 int /*<<< orphan*/  interpreter ; 
 int readline_active ; 
 scalar_t__ readline_disabled ; 
 void* rl_basic_word_break_characters ; 
 int /*<<< orphan*/  rl_callback_handler_install (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_completion_entry_function ; 
 void* rl_filename_quote_characters ; 
 void* strdup (char*) ; 

void set_interface_callbacks (void) {
  if (readline_disabled) { return; }
  readline_active = 1;
  rl_filename_quote_characters = strdup (" ");
  rl_basic_word_break_characters = strdup (" ");
  
  
  rl_callback_handler_install (get_default_prompt (), interpreter);
  rl_completion_entry_function = command_generator;
}