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
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  DebugMemDontCheckThis (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DebugMemHandler ; 
 int /*<<< orphan*/  Die (char*) ; 
 int /*<<< orphan*/ * cmsCreateContext (int /*<<< orphan*/ *,void*) ; 

cmsContext WatchDogContext(void* usr)
{
    cmsContext ctx;

    ctx = cmsCreateContext(&DebugMemHandler, usr);

    if (ctx == NULL)
        Die("Unable to create memory managed context");

    DebugMemDontCheckThis(ctx);
    return ctx;
}