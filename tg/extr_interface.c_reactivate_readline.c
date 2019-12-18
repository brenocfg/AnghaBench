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
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_default_prompt () ; 
 int /*<<< orphan*/  one_string ; 
 int one_string_flags ; 
 char* one_string_len ; 
 char* one_string_prompt ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ read_one_string ; 
 int /*<<< orphan*/  rl_point ; 
 int /*<<< orphan*/  rl_redisplay () ; 
 int /*<<< orphan*/  rl_replace_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saved_line ; 
 int /*<<< orphan*/  saved_point ; 
 int /*<<< orphan*/  set_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void reactivate_readline (void) {
  if (read_one_string) {
    printf ("%s ", one_string_prompt);
    if (!(one_string_flags & 1)) {
      printf ("%.*s", one_string_len, one_string);
    }
    fflush (stdout);
  } else {
    set_prompt (get_default_prompt ());
    rl_replace_line(saved_line, 0);
    rl_point = saved_point;
    rl_redisplay();
    free (saved_line);
  }
}