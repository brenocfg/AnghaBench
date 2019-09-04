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
struct options_entry {int dummy; } ;
struct options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 struct options_entry* options_get (struct options*,char*) ; 
 struct options_entry* options_get_only (struct options*,char*) ; 
 char* options_parse (char const*,int*) ; 

struct options_entry *
options_parse_get(struct options *oo, const char *s, int *idx, int only)
{
	struct options_entry	*o;
	char			*name;

	name = options_parse(s, idx);
	if (name == NULL)
		return (NULL);
	if (only)
		o = options_get_only(oo, name);
	else
		o = options_get(oo, name);
	free(name);
	return (o);
}