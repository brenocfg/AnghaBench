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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_data; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (TYPE_1__* const,TYPE_2__* const) ; 
 int /*<<< orphan*/  FilterCallback ; 
 unsigned int NUM_ADJUST_MODES ; 
 int /*<<< orphan*/ * adjust_params_names ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CloseAdjust(vlc_object_t * obj)
{
    filter_t *const     filter = (filter_t *)obj;
    filter_sys_t *const filter_sys = filter->p_sys;

    for (unsigned int i = 0; i < NUM_ADJUST_MODES; ++i)
    {
        var_DelCallback(obj, adjust_params_names[i],
                        FilterCallback, filter_sys->p_data);
        var_Destroy(obj, adjust_params_names[i]);
    }
    free(filter_sys->p_data);
    Close(filter, filter_sys);
}