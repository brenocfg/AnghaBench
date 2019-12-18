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
 int /*<<< orphan*/  assert (scalar_t__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ read_one_string ; 
 int rl_end ; 
 int /*<<< orphan*/  rl_line_buffer ; 
 int /*<<< orphan*/  rl_point ; 
 int /*<<< orphan*/  rl_redisplay () ; 
 int /*<<< orphan*/  rl_replace_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_save_prompt () ; 
 scalar_t__* saved_line ; 
 int /*<<< orphan*/  saved_point ; 
 int /*<<< orphan*/  stdout ; 

void deactivate_readline (void) {
  if (read_one_string) {
    printf ("\033[2K\r");
    fflush (stdout);
  } else {
    saved_point = rl_point;
    saved_line = malloc (rl_end + 1);
    assert (saved_line);
    saved_line[rl_end] = 0;
    memcpy (saved_line, rl_line_buffer, rl_end);

    rl_save_prompt();
    rl_replace_line("", 0);
    rl_redisplay();
  }
}