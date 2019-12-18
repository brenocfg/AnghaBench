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
struct args_value {int /*<<< orphan*/  value; } ;
struct args_entry {char* flag; } ;

/* Variables and functions */
 char* args_escape (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args_print_add (char**,size_t*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
args_print_add_value(char **buf, size_t *len, struct args_entry *entry,
    struct args_value *value)
{
	char	*escaped;

	if (**buf != '\0')
		args_print_add(buf, len, " -%c ", entry->flag);
	else
		args_print_add(buf, len, "-%c ", entry->flag);

	escaped = args_escape(value->value);
	args_print_add(buf, len, "%s", escaped);
	free(escaped);
}