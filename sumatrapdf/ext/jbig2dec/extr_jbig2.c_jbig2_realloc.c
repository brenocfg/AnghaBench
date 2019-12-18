#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* (* realloc ) (TYPE_1__*,void*,size_t) ;} ;
typedef  TYPE_1__ Jbig2Allocator ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 void* stub1 (TYPE_1__*,void*,size_t) ; 

void *
jbig2_realloc(Jbig2Allocator *allocator, void *p, size_t size, size_t num)
{
    /* check for integer multiplication overflow */
    if (num > 0 && size >= SIZE_MAX / num)
        return NULL;
    return allocator->realloc(allocator, p, size * num);
}