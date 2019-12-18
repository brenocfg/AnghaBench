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
struct TYPE_4__ {unsigned int surface_count; int /*<<< orphan*/ * surface; } ;
typedef  TYPE_1__ va_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  va_pool_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  va_surface_Release (int /*<<< orphan*/ *) ; 

void va_pool_Close(va_pool_t *va_pool)
{
    for (unsigned i = 0; i < va_pool->surface_count; i++)
        va_surface_Release(&va_pool->surface[i]);
    va_pool->surface_count = 0;

    va_pool_Release(va_pool);
}