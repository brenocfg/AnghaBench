#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ char_u ;
struct TYPE_2__ {int flags; scalar_t__** def_val; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NUL ; 
 int P_WAS_SET ; 
 size_t VI_DEFAULT ; 
 int findoption (scalar_t__*) ; 
 scalar_t__ fnamecmp (scalar_t__*,char*) ; 
 scalar_t__* gettail (scalar_t__*) ; 
 int /*<<< orphan*/  mb_ptr_adv (scalar_t__*) ; 
 TYPE_1__* options ; 
 scalar_t__* p_sh ; 
 void* p_shcf ; 
 scalar_t__* p_shq ; 
 void* p_sp ; 
 void* p_srr ; 
 void* p_sxq ; 
 int /*<<< orphan*/  set_title_defaults () ; 
 scalar_t__* skiptowhite (scalar_t__*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  vim_free (scalar_t__*) ; 
 scalar_t__ vim_ispathsep (scalar_t__) ; 
 scalar_t__* vim_strnsave (scalar_t__*,int) ; 
 scalar_t__* vim_strsave (scalar_t__*) ; 

void
set_init_3()
{
#if defined(UNIX) || defined(OS2) || defined(WIN3264)
/*
 * Set 'shellpipe' and 'shellredir', depending on the 'shell' option.
 * This is done after other initializations, where 'shell' might have been
 * set, but only if they have not been set before.
 */
    char_u  *p;
    int	    idx_srr;
    int	    do_srr;
#ifdef FEAT_QUICKFIX
    int	    idx_sp;
    int	    do_sp;
#endif

    idx_srr = findoption((char_u *)"srr");
    if (idx_srr < 0)
	do_srr = FALSE;
    else
	do_srr = !(options[idx_srr].flags & P_WAS_SET);
#ifdef FEAT_QUICKFIX
    idx_sp = findoption((char_u *)"sp");
    if (idx_sp < 0)
	do_sp = FALSE;
    else
	do_sp = !(options[idx_sp].flags & P_WAS_SET);
#endif

    /*
     * Isolate the name of the shell:
     * - Skip beyond any path.  E.g., "/usr/bin/csh -f" -> "csh -f".
     * - Remove any argument.  E.g., "csh -f" -> "csh".
     * But don't allow a space in the path, so that this works:
     *   "/usr/bin/csh --rcfile ~/.cshrc"
     * But don't do that for Windows, it's common to have a space in the path.
     */
#ifdef WIN3264
    p = gettail(p_sh);
    p = vim_strnsave(p, (int)(skiptowhite(p) - p));
#else
    p = skiptowhite(p_sh);
    if (*p == NUL)
    {
	/* No white space, use the tail. */
	p = vim_strsave(gettail(p_sh));
    }
    else
    {
	char_u  *p1, *p2;

	/* Find the last path separator before the space. */
	p1 = p_sh;
	for (p2 = p_sh; p2 < p; mb_ptr_adv(p2))
	    if (vim_ispathsep(*p2))
		p1 = p2 + 1;
	p = vim_strnsave(p1, (int)(p - p1));
    }
#endif
    if (p != NULL)
    {
	/*
	 * Default for p_sp is "| tee", for p_srr is ">".
	 * For known shells it is changed here to include stderr.
	 */
	if (	   fnamecmp(p, "csh") == 0
		|| fnamecmp(p, "tcsh") == 0
# if defined(OS2) || defined(WIN3264)	/* also check with .exe extension */
		|| fnamecmp(p, "csh.exe") == 0
		|| fnamecmp(p, "tcsh.exe") == 0
# endif
	   )
	{
#if defined(FEAT_QUICKFIX)
	    if (do_sp)
	    {
# ifdef WIN3264
		p_sp = (char_u *)">&";
# else
		p_sp = (char_u *)"|& tee";
# endif
		options[idx_sp].def_val[VI_DEFAULT] = p_sp;
	    }
#endif
	    if (do_srr)
	    {
		p_srr = (char_u *)">&";
		options[idx_srr].def_val[VI_DEFAULT] = p_srr;
	    }
	}
	else
# ifndef OS2	/* Always use bourne shell style redirection if we reach this */
	    if (       fnamecmp(p, "sh") == 0
		    || fnamecmp(p, "ksh") == 0
		    || fnamecmp(p, "mksh") == 0
		    || fnamecmp(p, "pdksh") == 0
		    || fnamecmp(p, "zsh") == 0
		    || fnamecmp(p, "zsh-beta") == 0
		    || fnamecmp(p, "bash") == 0
#  ifdef WIN3264
		    || fnamecmp(p, "cmd") == 0
		    || fnamecmp(p, "sh.exe") == 0
		    || fnamecmp(p, "ksh.exe") == 0
		    || fnamecmp(p, "mksh.exe") == 0
		    || fnamecmp(p, "pdksh.exe") == 0
		    || fnamecmp(p, "zsh.exe") == 0
		    || fnamecmp(p, "zsh-beta.exe") == 0
		    || fnamecmp(p, "bash.exe") == 0
		    || fnamecmp(p, "cmd.exe") == 0
#  endif
		    )
# endif
	    {
#if defined(FEAT_QUICKFIX)
		if (do_sp)
		{
# ifdef WIN3264
		    p_sp = (char_u *)">%s 2>&1";
# else
		    p_sp = (char_u *)"2>&1| tee";
# endif
		    options[idx_sp].def_val[VI_DEFAULT] = p_sp;
		}
#endif
		if (do_srr)
		{
		    p_srr = (char_u *)">%s 2>&1";
		    options[idx_srr].def_val[VI_DEFAULT] = p_srr;
		}
	    }
	vim_free(p);
    }
#endif

#if defined(MSDOS) || defined(WIN3264) || defined(OS2)
    /*
     * Set 'shellcmdflag', 'shellxquote', and 'shellquote' depending on the
     * 'shell' option.
     * This is done after other initializations, where 'shell' might have been
     * set, but only if they have not been set before.  Default for p_shcf is
     * "/c", for p_shq is "".  For "sh" like  shells it is changed here to
     * "-c" and "\"", but not for DJGPP, because it starts the shell without
     * command.com.  And for Win32 we need to set p_sxq instead.
     */
    if (strstr((char *)gettail(p_sh), "sh") != NULL)
    {
	int	idx3;

	idx3 = findoption((char_u *)"shcf");
	if (idx3 >= 0 && !(options[idx3].flags & P_WAS_SET))
	{
	    p_shcf = (char_u *)"-c";
	    options[idx3].def_val[VI_DEFAULT] = p_shcf;
	}

# ifndef DJGPP
#  ifdef WIN3264
	/* Somehow Win32 requires the quotes around the redirection too */
	idx3 = findoption((char_u *)"sxq");
	if (idx3 >= 0 && !(options[idx3].flags & P_WAS_SET))
	{
	    p_sxq = (char_u *)"\"";
	    options[idx3].def_val[VI_DEFAULT] = p_sxq;
	}
#  else
	idx3 = findoption((char_u *)"shq");
	if (idx3 >= 0 && !(options[idx3].flags & P_WAS_SET))
	{
	    p_shq = (char_u *)"\"";
	    options[idx3].def_val[VI_DEFAULT] = p_shq;
	}
#  endif
# endif
    }
    else if (strstr((char *)gettail(p_sh), "cmd.exe") != NULL)
    {
	int	idx3;

	/*
	 * cmd.exe on Windows will strip the first and last double quote given
	 * on the command line, e.g. most of the time things like:
	 *   cmd /c "my path/to/echo" "my args to echo"
	 * become:
	 *   my path/to/echo" "my args to echo
	 * when executed.
	 *
	 * To avoid this, set shellxquote to surround the command in
	 * parenthesis.  This appears to make most commands work, without
	 * breaking commands that worked previously, such as
	 * '"path with spaces/cmd" "a&b"'.
	 */
	idx3 = findoption((char_u *)"sxq");
	if (idx3 >= 0 && !(options[idx3].flags & P_WAS_SET))
	{
	    p_sxq = (char_u *)"(";
	    options[idx3].def_val[VI_DEFAULT] = p_sxq;
	}

	idx3 = findoption((char_u *)"shcf");
	if (idx3 >= 0 && !(options[idx3].flags & P_WAS_SET))
	{
	    p_shcf = (char_u *)"/c";
	    options[idx3].def_val[VI_DEFAULT] = p_shcf;
	}
    }
#endif

#ifdef FEAT_TITLE
    set_title_defaults();
#endif
}