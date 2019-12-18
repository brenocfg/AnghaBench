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
 size_t SIZE_MAX ; 
 void* ar_malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *ar_calloc(size_t count, size_t size)
{
    void *ptr = NULL;
    if (size <= SIZE_MAX / count)
        ptr = ar_malloc(count * size);
    if (ptr)
        memset(ptr, 0, count * size);
    return ptr;
}