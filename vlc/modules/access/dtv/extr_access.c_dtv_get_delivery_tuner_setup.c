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
typedef  int /*<<< orphan*/ * tuner_setup_t ;
typedef  scalar_t__ dtv_delivery_t ;
struct TYPE_3__ {scalar_t__ delivery; int /*<<< orphan*/ * pf_setup; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* delsys_mappings ; 

tuner_setup_t dtv_get_delivery_tuner_setup( dtv_delivery_t d )
{
    for (size_t i=0; i<ARRAY_SIZE(delsys_mappings); i++)
    {
        if ( delsys_mappings[i].delivery == d )
            return delsys_mappings[i].pf_setup;
    }
    return NULL;
}