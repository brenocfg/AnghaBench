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
 int OK ; 
 int /*<<< orphan*/  PyErr_SetVim (char*) ; 
 scalar_t__ VimTryEnd () ; 
 int /*<<< orphan*/ * set_option_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
set_option_value_err(char_u *key, int numval, char_u *stringval, int opt_flags)
{
    char_u	*errmsg;

    if ((errmsg = set_option_value(key, numval, stringval, opt_flags)))
    {
	if (VimTryEnd())
	    return FAIL;
	PyErr_SetVim((char *)errmsg);
	return FAIL;
    }
    return OK;
}