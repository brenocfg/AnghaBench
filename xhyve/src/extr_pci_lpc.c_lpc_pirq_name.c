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
 int /*<<< orphan*/  asprintf (char**,char*,char) ; 
 int /*<<< orphan*/ * lpc_bridge ; 

char *
lpc_pirq_name(int pin)
{
	char *name;

	if (lpc_bridge == NULL)
		return (NULL);
	asprintf(&name, "\\_SB.PC00.ISA.LNK%c,", 'A' + pin - 1);
	return (name);
}