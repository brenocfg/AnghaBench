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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  STRCAT (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STRCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  p_go ; 
 int /*<<< orphan*/  set_option_value (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  workshopInitDone ; 
 int /*<<< orphan*/  wstrace (char*) ; 

void
workshop_toolbar_end()
{
    char_u	buf[64];

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
    {
	wstrace("workshop_toolbar_end()\n");
    }
#endif

    /*
     * Turn on ToolBar.
     */
    STRCPY(buf, p_go);
    if (vim_strchr(p_go, 'T') == NULL)
    {
	STRCAT(buf, "T");
	set_option_value((char_u *)"go", 0L, buf, 0);
    }
    workshopInitDone = True;
}