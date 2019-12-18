#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* pf_deinit ) (TYPE_2__*) ;} ;
struct TYPE_7__ {struct TYPE_7__* p_extra; TYPE_1__ cb; } ;
typedef  TYPE_2__ mux_extradata_builder_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void mux_extradata_builder_Delete(mux_extradata_builder_t *m)
{
    if(m->cb.pf_deinit)
        m->cb.pf_deinit(m);
    free(m->p_extra);
    free(m);
}