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
 int FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 char* FullName_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char NUL ; 
 int OK ; 
 char* exe_name ; 
 scalar_t__ isatty (int) ; 
 char* searchpath (char*) ; 

int
mch_check_win(
    int		argc,
    char	**argv)
{
    /* store argv[0], may be used for $VIM */
    if (*argv[0] != NUL)
	exe_name = FullName_save((char_u *)argv[0], FALSE);

    /*
     * Try the DOS search path.  The executable may in
     * fact be called differently, so try this last.
     */
    if (exe_name == NULL || *exe_name == NUL)
	exe_name = searchpath("vim.exe");

    if (isatty(1))
	return OK;
    return FAIL;
}