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

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_curdir ; 
 int /*<<< orphan*/  e_sandbox ; 
 scalar_t__ sandbox ; 
 int secure ; 

int
check_secure()
{
    if (secure)
    {
	secure = 2;
	EMSG(_(e_curdir));
	return TRUE;
    }
#ifdef HAVE_SANDBOX
    /*
     * In the sandbox more things are not allowed, including the things
     * disallowed in secure mode.
     */
    if (sandbox != 0)
    {
	EMSG(_(e_sandbox));
	return TRUE;
    }
#endif
    return FALSE;
}