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
 int FALSE ; 
 char NUL ; 
 scalar_t__ STRLEN (char*) ; 
 int TRUE ; 
 int _MAX_PATH ; 
 int /*<<< orphan*/  copy_option_part (char**,char*,int,char*) ; 
 scalar_t__ executable_exists (char*) ; 
 scalar_t__ gettail (char*) ; 
 char* mch_getenv (char*) ; 
 char* p_sh ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/ * vim_strchr (scalar_t__,char) ; 
 int /*<<< orphan*/  vim_strncpy (char*,char*,int) ; 

int
mch_can_exe(char_u *name)
{
    char_u	buf[_MAX_PATH];
    int		len = (int)STRLEN(name);
    char_u	*p;

    if (len >= _MAX_PATH)	/* safety check */
	return FALSE;

    /* If there already is an extension try using the name directly.  Also do
     * this with a Unix-shell like 'shell'. */
    if (vim_strchr(gettail(name), '.') != NULL
			       || strstr((char *)gettail(p_sh), "sh") != NULL)
	if (executable_exists((char *)name))
	    return TRUE;

    /*
     * Loop over all extensions in $PATHEXT.
     */
    vim_strncpy(buf, name, _MAX_PATH - 1);
    p = mch_getenv("PATHEXT");
    if (p == NULL)
	p = (char_u *)".com;.exe;.bat;.cmd";
    while (*p)
    {
	if (p[0] == '.' && (p[1] == NUL || p[1] == ';'))
	{
	    /* A single "." means no extension is added. */
	    buf[len] = NUL;
	    ++p;
	    if (*p)
		++p;
	}
	else
	    copy_option_part(&p, buf + len, _MAX_PATH - len, ";");
	if (executable_exists((char *)buf))
	    return TRUE;
    }
    return FALSE;
}