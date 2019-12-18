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
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ cmdwin_type ; 
 int /*<<< orphan*/  e_cmdwin ; 
 int /*<<< orphan*/  e_secure ; 

void
text_locked_msg()
{
#ifdef FEAT_CMDWIN
    if (cmdwin_type != 0)
	EMSG(_(e_cmdwin));
    else
#endif
	EMSG(_(e_secure));
}