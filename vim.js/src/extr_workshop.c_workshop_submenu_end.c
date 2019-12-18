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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 char NUL ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  curMenuName ; 
 int /*<<< orphan*/  curMenuPriority ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wstrace (char*) ; 

void
workshop_submenu_end()
{
    char		*p;

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE)
	    && strncmp(curMenuName, "ToolBar", 7) != 0)
	wstrace("workshop_submenu_end()\n");
#endif

    p = strrchr(curMenuPriority, '.');
    ASSERT(p != NULL);
    *p = NUL;

    p = strrchr(curMenuName, '.');
    ASSERT(p != NULL);
    *p = NUL;
}