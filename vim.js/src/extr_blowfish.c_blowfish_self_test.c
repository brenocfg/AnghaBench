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
 scalar_t__ FAIL ; 
 int OK ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bf_self_test () ; 
 scalar_t__ sha256_self_test () ; 

int
blowfish_self_test()
{
    if (sha256_self_test() == FAIL)
    {
	EMSG(_("E818: sha256 test failed"));
	return FAIL;
    }
    if (bf_self_test() == FAIL)
    {
	EMSG(_("E819: Blowfish test failed"));
	return FAIL;
    }
    return OK;
}