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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,size_t,void*,char const*,int) ; 
 int /*<<< orphan*/  log_error (char*,size_t,char const*,int) ; 
 void* realloc (void*,size_t) ; 

void *
_nc_realloc(void *ptr, size_t size, const char *name, int line)
{
    void *p;

    ASSERT(size != 0);

    p = realloc(ptr, size);
    if (p == NULL) {
        log_error("realloc(%zu) failed @ %s:%d", size, name, line);
    } else {
        log_debug(LOG_VVERB, "realloc(%zu) at %p @ %s:%d", size, p, name, line);
    }

    return p;
}