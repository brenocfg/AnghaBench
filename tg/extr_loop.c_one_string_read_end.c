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
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  do_get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one_string ; 
 int /*<<< orphan*/  one_string_cb (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 size_t one_string_num ; 
 int /*<<< orphan*/ * one_string_prompt ; 
 int /*<<< orphan*/ ** one_string_results ; 
 size_t one_string_total_args ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reactivate_readline () ; 
 scalar_t__ read_one_string ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  string_cb_arg ; 
 int /*<<< orphan*/  tfree_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void one_string_read_end (void) {
  printf ("\n");
  fflush (stdout);

  read_one_string = 0;
  tfree_str (one_string_prompt);
  one_string_prompt = NULL;
  reactivate_readline ();

  one_string_results[one_string_num] = tstrdup (one_string);
  ++one_string_num;

  if (one_string_num < one_string_total_args) {
    do_get_string (TLS);
  } else {
    one_string_cb (TLS, (void *)one_string_results, string_cb_arg);
    int i;
    for (i = 0; i < one_string_total_args; i++) {
      tfree_str (one_string_results[i]);
    }
  }
}