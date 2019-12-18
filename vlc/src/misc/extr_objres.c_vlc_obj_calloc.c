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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mul_overflow (size_t,size_t,size_t*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 void* vlc_obj_malloc (int /*<<< orphan*/ *,size_t) ; 

void *vlc_obj_calloc(vlc_object_t *obj, size_t nmemb, size_t size)
{
    size_t tabsize;
    if (unlikely(mul_overflow(nmemb, size, &tabsize)))
    {
        errno = ENOMEM;
        return NULL;
    }

    void *ptr = vlc_obj_malloc(obj, tabsize);
    if (likely(ptr != NULL))
        memset(ptr, 0, tabsize);
    return ptr;
}