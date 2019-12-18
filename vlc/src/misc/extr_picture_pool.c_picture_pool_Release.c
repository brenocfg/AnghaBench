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
struct TYPE_4__ {unsigned int picture_count; int /*<<< orphan*/ * picture; } ;
typedef  TYPE_1__ picture_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_pool_Destroy (TYPE_1__*) ; 

void picture_pool_Release(picture_pool_t *pool)
{
    for (unsigned i = 0; i < pool->picture_count; i++)
        picture_Release(pool->picture[i]);
    picture_pool_Destroy(pool);
}