#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_module; } ;
typedef  TYPE_1__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

__attribute__((used)) static void aout_FiltersPipelineDestroy(filter_t *const *filters, unsigned n)
{
    for( unsigned i = 0; i < n; i++ )
    {
        filter_t *p_filter = filters[i];

        module_unneed( p_filter, p_filter->p_module );
        vlc_object_delete(p_filter);
    }
}