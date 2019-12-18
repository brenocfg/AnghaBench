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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_release ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 void* vlc_objres_new (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_objres_push (int /*<<< orphan*/ *,void*) ; 

void *vlc_obj_malloc(vlc_object_t *obj, size_t size)
{
    void *ptr = vlc_objres_new(size, dummy_release);
    if (likely(ptr != NULL))
        vlc_objres_push(obj, ptr);
    return ptr;
}