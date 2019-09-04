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
struct args_value {char* value; } ;
struct args_entry {char* flag; } ;

/* Variables and functions */
 int VIS_DQ ; 
 int VIS_NL ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 int /*<<< orphan*/  args_print_add (char**,size_t*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t strcspn (char*,char const*) ; 
 int /*<<< orphan*/  utf8_stravis (char**,char*,int) ; 

__attribute__((used)) static void
args_print_add_value(char **buf, size_t *len, struct args_entry *entry,
    struct args_value *value)
{
	static const char	 quoted[] = " #\"';$";
	char			*escaped;
	int			 flags;

	if (**buf != '\0')
		args_print_add(buf, len, " -%c ", entry->flag);
	else
		args_print_add(buf, len, "-%c ", entry->flag);

	flags = VIS_OCTAL|VIS_TAB|VIS_NL;
	if (value->value[strcspn(value->value, quoted)] != '\0')
		flags |= VIS_DQ;
	utf8_stravis(&escaped, value->value, flags);
	if (flags & VIS_DQ)
		args_print_add(buf, len, "\"%s\"", escaped);
	else
		args_print_add(buf, len, "%s", escaped);
	free(escaped);
}