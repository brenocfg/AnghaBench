#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cbuf ;
struct TYPE_3__ {int /*<<< orphan*/ * accel; int /*<<< orphan*/  verb; } ;
typedef  TYPE_1__ MenuMap ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* menuMap ; 
 size_t menuMapSize ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,int /*<<< orphan*/ *,...) ; 
 scalar_t__ workshopHotKeysEnabled ; 
 int /*<<< orphan*/  wstrace (char*,char*) ; 

void
workshop_hotkeys(
	Boolean	on)
{
    char	 cbuf[BUFSIZ];		/* command buffer */
    MenuMap	*mp;			/* iterate over menuMap entries */

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_hotkeys(%s)\n", on ? "True" : "False");
#endif

    workshopHotKeysEnabled = on;
    if (workshopHotKeysEnabled)
	for (mp = menuMap; mp < &menuMap[menuMapSize]; mp++)
	{
	    if (mp->accel != NULL)
	    {
		vim_snprintf(cbuf, sizeof(cbuf),
			"map %s :wsverb %s<CR>", mp->accel, mp->verb);
		coloncmd(cbuf, TRUE);
	    }
	}
    else
	for (mp = menuMap; mp < &menuMap[menuMapSize]; mp++)
	{
	    if (mp->accel != NULL)
	    {
		vim_snprintf(cbuf, sizeof(cbuf), "unmap %s", mp->accel);
		coloncmd(cbuf, TRUE);
	    }
	}
}