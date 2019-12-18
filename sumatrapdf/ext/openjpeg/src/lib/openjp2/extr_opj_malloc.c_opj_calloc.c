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
 void* calloc (size_t,size_t) ; 

void * opj_calloc(size_t num, size_t size)
{
    if (num == 0 || size == 0) {
        /* prevent implementation defined behavior of realloc */
        return NULL;
    }
    return calloc(num, size);
}