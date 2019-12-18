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
typedef  int /*<<< orphan*/  win_T ;
typedef  int /*<<< orphan*/  tabpage_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  buf_T ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
#define  SREQ_BUF 130 
#define  SREQ_GLOBAL 129 
#define  SREQ_WIN 128 
 int /*<<< orphan*/  TRUE ; 
 int VimTryEnd () ; 
 int /*<<< orphan*/  VimTryStart () ; 
 int /*<<< orphan*/  restore_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_win (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int set_option_value_err (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  switch_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int switch_win (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_find_tabpage (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_option_value_for(
	char_u *key,
	int numval,
	char_u *stringval,
	int opt_flags,
	int opt_type,
	void *from)
{
    win_T	*save_curwin = NULL;
    tabpage_T	*save_curtab = NULL;
    buf_T	*save_curbuf = NULL;
    int		set_ret = 0;

    VimTryStart();
    switch (opt_type)
    {
	case SREQ_WIN:
	    if (switch_win(&save_curwin, &save_curtab, (win_T *)from,
			      win_find_tabpage((win_T *)from), FALSE) == FAIL)
	    {
		if (VimTryEnd())
		    return -1;
		PyErr_SET_VIM(N_("problem while switching windows"));
		return -1;
	    }
	    set_ret = set_option_value_err(key, numval, stringval, opt_flags);
	    restore_win(save_curwin, save_curtab, TRUE);
	    break;
	case SREQ_BUF:
	    switch_buffer(&save_curbuf, (buf_T *)from);
	    set_ret = set_option_value_err(key, numval, stringval, opt_flags);
	    restore_buffer(save_curbuf);
	    break;
	case SREQ_GLOBAL:
	    set_ret = set_option_value_err(key, numval, stringval, opt_flags);
	    break;
    }
    if (set_ret == FAIL)
	return -1;
    return VimTryEnd();
}