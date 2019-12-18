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
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static void *memalign(size_t align, size_t size)
{
    void *p = malloc(size);

    if ((uintptr_t)p & (align - 1)) {
        free(p);
        p = NULL;
    }

    return p;
}