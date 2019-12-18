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
struct TYPE_3__ {int /*<<< orphan*/  poolrefs; } ;
typedef  TYPE_1__ va_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void va_pool_AddRef(va_pool_t *va_pool)
{
    atomic_fetch_add(&va_pool->poolrefs, 1);
}