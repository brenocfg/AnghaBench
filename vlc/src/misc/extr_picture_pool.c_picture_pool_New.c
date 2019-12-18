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
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  picture_pool_t ;
struct TYPE_3__ {unsigned int picture_count; int /*<<< orphan*/ * const* picture; } ;
typedef  TYPE_1__ picture_pool_configuration_t ;

/* Variables and functions */
 int /*<<< orphan*/ * picture_pool_NewExtended (TYPE_1__*) ; 

picture_pool_t *picture_pool_New(unsigned count, picture_t *const *tab)
{
    picture_pool_configuration_t cfg = {
        .picture_count = count,
        .picture = tab,
    };

    return picture_pool_NewExtended(&cfg);
}