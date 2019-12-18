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
 scalar_t__ getenv (char*) ; 
 int ngx_debug_malloc ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 

void
ngx_debug_init(void)
{
#if (NGX_DEBUG_MALLOC)

    /*
     * MacOSX 10.6, 10.7:  MallocScribble fills freed memory with 0x55
     *                     and fills allocated memory with 0xAA.
     * MacOSX 10.4, 10.5:  MallocScribble fills freed memory with 0x55,
     *                     MallocPreScribble fills allocated memory with 0xAA.
     * MacOSX 10.3:        MallocScribble fills freed memory with 0x55,
     *                     and no way to fill allocated memory.
     */

    setenv("MallocScribble", "1", 0);

    ngx_debug_malloc = 1;

#else

    if (getenv("MallocScribble")) {
        ngx_debug_malloc = 1;
    }

#endif
}