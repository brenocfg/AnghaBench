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
struct client {struct client* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsnprintf (char*,int,char*,struct client*) ; 

__attribute__((used)) static const char *
cmdq_name(struct client *c)
{
	static char	s[256];

	if (c == NULL)
		return ("<global>");
	if (c->name != NULL)
		xsnprintf(s, sizeof s, "<%s>", c->name);
	else
		xsnprintf(s, sizeof s, "<%p>", c);
	return (s);
}