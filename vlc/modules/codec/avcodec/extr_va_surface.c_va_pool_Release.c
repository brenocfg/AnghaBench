#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* pf_destroy_device ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ callbacks; int /*<<< orphan*/  poolrefs; } ;
typedef  TYPE_2__ va_pool_t ;

/* Variables and functions */
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void va_pool_Release(va_pool_t *va_pool)
{
    if (atomic_fetch_sub(&va_pool->poolrefs, 1) != 1)
        return;

    va_pool->callbacks.pf_destroy_device(va_pool->callbacks.opaque);

    free(va_pool);
}