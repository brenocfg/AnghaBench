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
struct layout_cell {int dummy; } ;

/* Variables and functions */
 scalar_t__ layout_append (struct layout_cell*,char*,int) ; 
 int /*<<< orphan*/  layout_checksum (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 

char *
layout_dump(struct layout_cell *root)
{
	char	layout[8192], *out;

	*layout = '\0';
	if (layout_append(root, layout, sizeof layout) != 0)
		return (NULL);

	xasprintf(&out, "%04hx,%s", layout_checksum(layout), layout);
	return (out);
}