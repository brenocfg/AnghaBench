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
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetNone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetVim (char*) ; 
 int /*<<< orphan*/  PyExc_KeyboardInterrupt ; 
 TYPE_1__* current_exception ; 
 void* did_emsg ; 
 void* did_throw ; 
 int /*<<< orphan*/  discard_current_exception () ; 
 void* got_int ; 
 void* need_rethrow ; 
 int /*<<< orphan*/  trylevel ; 

__attribute__((used)) static int
VimTryEnd(void)
{
    --trylevel;
    /* Without this it stops processing all subsequent VimL commands and
     * generates strange error messages if I e.g. try calling Test() in a
     * cycle */
    did_emsg = FALSE;
    /* Keyboard interrupt should be preferred over anything else */
    if (got_int)
    {
	if (current_exception != NULL)
	    discard_current_exception();
	else
	    need_rethrow = did_throw = FALSE;
	got_int = FALSE;
	PyErr_SetNone(PyExc_KeyboardInterrupt);
	return -1;
    }
    else if (!did_throw)
	return (PyErr_Occurred() ? -1 : 0);
    /* Python exception is preferred over vim one; unlikely to occur though */
    else if (PyErr_Occurred())
    {
	if (current_exception != NULL)
	    discard_current_exception();
	else
	    need_rethrow = did_throw = FALSE;
	return -1;
    }
    /* Finally transform VimL exception to python one */
    else
    {
	PyErr_SetVim((char *)current_exception->value);
	discard_current_exception();
	return -1;
    }
}