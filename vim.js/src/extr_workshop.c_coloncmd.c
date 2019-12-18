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
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ALT_INPUT_LOCK_OFF ; 
 int /*<<< orphan*/  ALT_INPUT_LOCK_ON ; 
 scalar_t__ WSDLEVEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WS_TRACE_COLONCMD ; 
 int /*<<< orphan*/  do_cmdline_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * empty_option ; 
 int /*<<< orphan*/  gui_update_screen () ; 
 int /*<<< orphan*/ * p_cpo ; 
 int /*<<< orphan*/  wsdebug (char*,char*) ; 

__attribute__((used)) static void
coloncmd(
	char	*cmd,		/* the command to print */
	Boolean	force)		/* force cursor update */
{
    char_u	*cpo_save = p_cpo;

#ifdef WSDEBUG
    if (WSDLEVEL(WS_TRACE_COLONCMD))
	wsdebug("Cmd: %s\n", cmd);
#endif

    p_cpo = empty_option;

    ALT_INPUT_LOCK_ON;
    do_cmdline_cmd((char_u *)cmd);
    ALT_INPUT_LOCK_OFF;

    p_cpo = cpo_save;

    if (force)
	gui_update_screen();
}