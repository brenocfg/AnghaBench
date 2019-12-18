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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,void*,char const*,int) ; 

void
_nc_free(void *ptr, const char *name, int line)
{
    ASSERT(ptr != NULL);
    log_debug(LOG_VVERB, "free(%p) @ %s:%d", ptr, name, line);
    free(ptr);
}