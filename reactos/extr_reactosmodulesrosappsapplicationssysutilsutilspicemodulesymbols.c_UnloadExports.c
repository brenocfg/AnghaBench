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
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PICE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pExports ; 

void UnloadExports(void)
{
	ENTER_FUNC();
	if(pExports)
	{
		DPRINT((0,"freeing %x\n",pExports));
		PICE_free(pExports);
        pExports = NULL;
	}
    LEAVE_FUNC();
}