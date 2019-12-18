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
struct tgl_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_readline () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_prompt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ one_string_len ; 
 int /*<<< orphan*/  one_string_num ; 
 char* one_string_prompt ; 
 int /*<<< orphan*/  one_string_type ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read_one_string ; 
 int /*<<< orphan*/  stdout ; 

void do_get_string (struct tgl_state *TLS) {
  deactivate_readline ();
  generate_prompt (one_string_type, one_string_num);  
  printf ("%s", one_string_prompt);
  fflush (stdout);
  read_one_string = 1;
  one_string_len = 0;  
}