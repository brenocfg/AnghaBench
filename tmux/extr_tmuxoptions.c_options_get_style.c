#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct style {int dummy; } ;
struct TYPE_2__ {struct style style; } ;
struct options_entry {TYPE_1__ value; } ;
struct options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTIONS_IS_STYLE (struct options_entry*) ; 
 int /*<<< orphan*/  fatalx (char*,char const*) ; 
 struct options_entry* options_get (struct options*,char const*) ; 

struct style *
options_get_style(struct options *oo, const char *name)
{
	struct options_entry	*o;

	o = options_get(oo, name);
	if (o == NULL)
		fatalx("missing option %s", name);
	if (!OPTIONS_IS_STYLE(o))
		fatalx("option %s is not a style", name);
	return (&o->value.style);
}