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
 int /*<<< orphan*/ * FullName_save (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ *,char*,int) ; 
 int MAX_ENV_PATH_LEN ; 
 char NUL ; 
 int /*<<< orphan*/  STRCAT (char*,char*) ; 
 int /*<<< orphan*/  STRCPY (char*,char*) ; 
 int STRLEN (char*) ; 
 int /*<<< orphan*/ * exe_name ; 
 char* exe_path ; 
 int /*<<< orphan*/ * gettail_sep (int /*<<< orphan*/ *) ; 
 char* mch_getenv (char*) ; 
 int /*<<< orphan*/  vim_setenv (char*,char*) ; 
 char* vim_strnsave (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
get_exe_name(void)
{
    /* Maximum length of $PATH is more than MAXPATHL.  8191 is often mentioned
     * as the maximum length that works (plus a NUL byte). */
#define MAX_ENV_PATH_LEN 8192
    char	temp[MAX_ENV_PATH_LEN];
    char_u	*p;

    if (exe_name == NULL)
    {
	/* store the name of the executable, may be used for $VIM */
	GetModuleFileName(NULL, temp, MAX_ENV_PATH_LEN - 1);
	if (*temp != NUL)
	    exe_name = FullName_save((char_u *)temp, FALSE);
    }

    if (exe_path == NULL && exe_name != NULL)
    {
	exe_path = vim_strnsave(exe_name,
				     (int)(gettail_sep(exe_name) - exe_name));
	if (exe_path != NULL)
	{
	    /* Append our starting directory to $PATH, so that when doing
	     * "!xxd" it's found in our starting directory.  Needed because
	     * SearchPath() also looks there. */
	    p = mch_getenv("PATH");
	    if (p == NULL
		       || STRLEN(p) + STRLEN(exe_path) + 2 < MAX_ENV_PATH_LEN)
	    {
		if (p == NULL || *p == NUL)
		    temp[0] = NUL;
		else
		{
		    STRCPY(temp, p);
		    STRCAT(temp, ";");
		}
		STRCAT(temp, exe_path);
		vim_setenv((char_u *)"PATH", temp);
	    }
	}
    }
}