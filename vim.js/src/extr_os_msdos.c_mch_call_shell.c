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
typedef  char char_u ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_PUTS (char*) ; 
 int SHELL_COOKED ; 
 int SHELL_SILENT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ STRLEN (char*) ; 
 int TMODE_COOK ; 
 int TMODE_RAW ; 
 int /*<<< orphan*/  TRUE ; 
 char* alloc (scalar_t__) ; 
 int cur_tmode ; 
 int /*<<< orphan*/  emsg_silent ; 
 int /*<<< orphan*/  msg_outnum (long) ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int /*<<< orphan*/  out_flush () ; 
 char* p_sh ; 
 char* p_shcf ; 
 int /*<<< orphan*/  set_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sys_cursor () ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  settmode (int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 int system (char*) ; 
 int /*<<< orphan*/  vim_free (char*) ; 

int
mch_call_shell(
    char_u	*cmd,
    int		options)
{
    int		x;
    int		tmode = cur_tmode;
#ifndef DJGPP
    char_u	*newcmd;
#endif

    out_flush();
#ifdef DJGPP
    set_sys_cursor();
#endif

    if (options & SHELL_COOKED)
	settmode(TMODE_COOK);	/* set to normal mode */
    set_interrupts(FALSE);	/* restore interrupts */

#ifdef DJGPP
    /* ignore signals while external command is running */
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
#endif
    if (cmd == NULL)
	x = system((char *)p_sh);
    else
    {
#ifdef DJGPP
	/*
	 * Use 'shell' for system().
	 */
	setenv("SHELL", (char *)p_sh, 1);
	x = system(cmd);
#else
	/* we use "command" to start the shell, slow but easy */
	newcmd = alloc(STRLEN(p_sh) + STRLEN(p_shcf) + STRLEN(cmd) + 3);
	if (newcmd == NULL)
	    x = -1;
	else
	{
	    sprintf((char *)newcmd, "%s %s %s", p_sh, p_shcf, cmd);
	    x = system((char *)newcmd);
	    vim_free(newcmd);
	}
#endif
    }
#ifdef DJGPP
    signal(SIGINT, SIG_DFL);
    signal(SIGHUP, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
#endif
    if (tmode == TMODE_RAW)
	settmode(TMODE_RAW);	/* set to raw mode */
    set_interrupts(TRUE);	/* catch interrupts */

    if (x && !(options & SHELL_SILENT) && !emsg_silent)
    {
	MSG_PUTS("\nshell returned ");
	msg_outnum((long)x);
	msg_putchar('\n');
    }

    return x;
}