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
 char* args_escape (char const*) ; 
 int /*<<< orphan*/  args_print_add (char**,size_t*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
args_print_add_argument(char **buf, size_t *len, const char *argument)
{
	char	*escaped;

	if (**buf != '\0')
		args_print_add(buf, len, " ");

	escaped = args_escape(argument);
	args_print_add(buf, len, "%s", escaped);
	free(escaped);
}