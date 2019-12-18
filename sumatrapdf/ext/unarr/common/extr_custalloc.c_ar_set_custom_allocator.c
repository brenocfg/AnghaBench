#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ custom_malloc_fn ;
typedef  scalar_t__ custom_free_fn ;
struct TYPE_2__ {void* opaque; scalar_t__ free; scalar_t__ malloc; } ;

/* Variables and functions */
 scalar_t__ default_free ; 
 scalar_t__ default_malloc ; 
 TYPE_1__ gAllocator ; 

void ar_set_custom_allocator(custom_malloc_fn custom_malloc, custom_free_fn custom_free, void *opaque)
{
    gAllocator.malloc = custom_malloc ? custom_malloc : default_malloc;
    gAllocator.free = custom_free ? custom_free : default_free;
    gAllocator.opaque = opaque;
}