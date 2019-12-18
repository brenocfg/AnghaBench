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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  GO_TEAROFF ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  gui_mch_toggle_tearoffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_go ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstrace (char*) ; 

void
workshop_menu_end()
{
    Boolean		 using_tearoff;	/* set per current option setting */

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_menu_end()\n");
#endif

    using_tearoff = vim_strchr(p_go, GO_TEAROFF) != NULL;
    gui_mch_toggle_tearoffs(using_tearoff);
}