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
typedef  scalar_t__ vtable_ptr ;

/* Variables and functions */
 scalar_t__* get_vtable (void*) ; 

__attribute__((used)) static inline void/*rtti_object_locator*/ *get_obj_locator( void *cppobj )
{
    const vtable_ptr *vtable = get_vtable( cppobj );
    return (void *)vtable[-1];
}