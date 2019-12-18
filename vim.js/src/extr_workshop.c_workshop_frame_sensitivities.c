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
struct TYPE_3__ {int sense; int /*<<< orphan*/ * verb; } ;
typedef  TYPE_1__ VerbSense ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_mch_flush () ; 
 int /*<<< orphan*/  gui_update_menus (int /*<<< orphan*/ ) ; 
 char* lookupVerb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ ws_debug ; 
 int /*<<< orphan*/  wsdebug (char*,...) ; 
 int /*<<< orphan*/  wstrace (char*) ; 

void
workshop_frame_sensitivities(
	VerbSense	*vs)		/* list of verbs to (de)sensitize */
{
    VerbSense	*vp;		/* iterate through vs */
    char	*menu_name;	/* used in menu lookup */
    int		 cnt;		/* count of verbs to skip */
    int		 len;		/* length of nonvariant part of command */
    char	 cbuf[4096];

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE) || WSDLEVEL(4))
    {
	wsdebug("workshop_frame_sensitivities(\n");
	for (vp = vs; vp->verb != NULL; vp++)
	    wsdebug("\t%-25s%d\n", vp->verb, vp->sense);
	wsdebug(")\n");
    }
    else if (WSDLEVEL(WS_TRACE))
	wstrace("workshop_frame_sensitivities()\n");
#endif
#ifdef WSDEBUG_SENSE
    if (ws_debug)
	for (vp = vs; vp->verb != NULL; vp++)
	    wsdebug("change: %-21.20s%-21.20s(%s)\n",
		    "", vp->verb, vp->sense == 1 ?
		    "Sensitive" : "Insensitive");
#endif

    /*
     * Look for all matching menu entries for the verb. There may be more
     * than one if the verb has both a menu and toolbar entry.
     */
    for (vp = vs; vp->verb != NULL; vp++)
    {
	cnt = 0;
	strcpy(cbuf, "amenu");
	strcat(cbuf, " ");
	strcat(cbuf, vp->sense ? "enable" : "disable");
	strcat(cbuf, " ");
	len = strlen(cbuf);
	while ((menu_name = lookupVerb(vp->verb, cnt++)) != NULL)
	{
	    strcpy(&cbuf[len], menu_name);
	    coloncmd(cbuf, FALSE);
	}
    }
    gui_update_menus(0);
    gui_mch_flush();
}