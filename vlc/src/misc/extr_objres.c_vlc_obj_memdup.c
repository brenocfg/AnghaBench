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
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 void* vlc_obj_malloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void *vlc_obj_memdup(vlc_object_t *obj, const void *base, size_t len)
{
    void *ptr = vlc_obj_malloc(obj, len);
    if (likely(ptr != NULL))
        memcpy(ptr, base, len);
    return ptr;
}