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
 void* _nc_alloc (size_t,char const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *
_nc_zalloc(size_t size, const char *name, int line)
{
    void *p;

    p = _nc_alloc(size, name, line);
    if (p != NULL) {
        memset(p, 0, size);
    }

    return p;
}