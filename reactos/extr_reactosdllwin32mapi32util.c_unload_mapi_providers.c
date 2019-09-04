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
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  mapi_ex_provider ; 
 int /*<<< orphan*/  mapi_provider ; 

void unload_mapi_providers(void)
{
    TRACE("()\n");

    FreeLibrary(mapi_provider);
    FreeLibrary(mapi_ex_provider);
}