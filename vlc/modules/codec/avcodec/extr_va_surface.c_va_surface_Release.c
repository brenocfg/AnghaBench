#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  va_pool; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ vlc_va_surface_t ;

/* Variables and functions */
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  va_pool_Release (int /*<<< orphan*/ ) ; 

void va_surface_Release(vlc_va_surface_t *surface)
{
    if (atomic_fetch_sub(&surface->refcount, 1) != 1)
        return;

    va_pool_Release(surface->va_pool);
}