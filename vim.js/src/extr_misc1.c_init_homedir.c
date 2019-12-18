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
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 scalar_t__ IOSIZE ; 
 char* IObuff ; 
 scalar_t__ MAXPATHL ; 
 char NUL ; 
 char* NameBuff ; 
 scalar_t__ OK ; 
 scalar_t__ STRLEN (char*) ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_to_enc (char*,int,char**,int*) ; 
 int /*<<< orphan*/  e_prev_dir ; 
 scalar_t__ enc_utf8 ; 
 char* homedir ; 
 scalar_t__ mch_chdir (char*) ; 
 scalar_t__ mch_dirname (char*,scalar_t__) ; 
 char* mch_getenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 int /*<<< orphan*/  vim_setenv (char*,char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,scalar_t__,char*,char*,char*) ; 
 char* vim_strchr (char*,char) ; 
 int /*<<< orphan*/  vim_strncpy (char*,char*,int) ; 
 char* vim_strsave (char*) ; 

void
init_homedir()
{
    char_u  *var;

    /* In case we are called a second time (when 'encoding' changes). */
    vim_free(homedir);
    homedir = NULL;

#ifdef VMS
    var = mch_getenv((char_u *)"SYS$LOGIN");
#else
    var = mch_getenv((char_u *)"HOME");
#endif

    if (var != NULL && *var == NUL)	/* empty is same as not set */
	var = NULL;

#ifdef WIN3264
    /*
     * Weird but true: $HOME may contain an indirect reference to another
     * variable, esp. "%USERPROFILE%".  Happens when $USERPROFILE isn't set
     * when $HOME is being set.
     */
    if (var != NULL && *var == '%')
    {
	char_u	*p;
	char_u	*exp;

	p = vim_strchr(var + 1, '%');
	if (p != NULL)
	{
	    vim_strncpy(NameBuff, var + 1, p - (var + 1));
	    exp = mch_getenv(NameBuff);
	    if (exp != NULL && *exp != NUL
					&& STRLEN(exp) + STRLEN(p) < MAXPATHL)
	    {
		vim_snprintf((char *)NameBuff, MAXPATHL, "%s%s", exp, p + 1);
		var = NameBuff;
		/* Also set $HOME, it's needed for _viminfo. */
		vim_setenv((char_u *)"HOME", NameBuff);
	    }
	}
    }

    /*
     * Typically, $HOME is not defined on Windows, unless the user has
     * specifically defined it for Vim's sake.  However, on Windows NT
     * platforms, $HOMEDRIVE and $HOMEPATH are automatically defined for
     * each user.  Try constructing $HOME from these.
     */
    if (var == NULL)
    {
	char_u *homedrive, *homepath;

	homedrive = mch_getenv((char_u *)"HOMEDRIVE");
	homepath = mch_getenv((char_u *)"HOMEPATH");
	if (homepath == NULL || *homepath == NUL)
	    homepath = "\\";
	if (homedrive != NULL
			   && STRLEN(homedrive) + STRLEN(homepath) < MAXPATHL)
	{
	    sprintf((char *)NameBuff, "%s%s", homedrive, homepath);
	    if (NameBuff[0] != NUL)
	    {
		var = NameBuff;
		/* Also set $HOME, it's needed for _viminfo. */
		vim_setenv((char_u *)"HOME", NameBuff);
	    }
	}
    }

# if defined(FEAT_MBYTE)
    if (enc_utf8 && var != NULL)
    {
	int	len;
	char_u  *pp = NULL;

	/* Convert from active codepage to UTF-8.  Other conversions are
	 * not done, because they would fail for non-ASCII characters. */
	acp_to_enc(var, (int)STRLEN(var), &pp, &len);
	if (pp != NULL)
	{
	    homedir = pp;
	    return;
	}
    }
# endif
#endif

#if defined(OS2) || defined(MSDOS) || defined(MSWIN)
    /*
     * Default home dir is C:/
     * Best assumption we can make in such a situation.
     */
    if (var == NULL)
	var = "C:/";
#endif
    if (var != NULL)
    {
#ifdef UNIX
	/*
	 * Change to the directory and get the actual path.  This resolves
	 * links.  Don't do it when we can't return.
	 */
	if (mch_dirname(NameBuff, MAXPATHL) == OK
					  && mch_chdir((char *)NameBuff) == 0)
	{
	    if (!mch_chdir((char *)var) && mch_dirname(IObuff, IOSIZE) == OK)
		var = IObuff;
	    if (mch_chdir((char *)NameBuff) != 0)
		EMSG(_(e_prev_dir));
	}
#endif
	homedir = vim_strsave(var);
    }
}