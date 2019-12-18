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
 scalar_t__ stderr ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlMemDisplay (scalar_t__) ; 

__attribute__((used)) static void debugmem_tag_error(void *p)
{
     xmlGenericError(xmlGenericErrorContext,
	     "Memory tag error occurs :%p \n\t bye\n", p);
#ifdef MEM_LIST
     if (stderr)
     xmlMemDisplay(stderr);
#endif
}