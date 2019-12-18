#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_5__ {unsigned int num_switchers; unsigned int* starts; unsigned int* lengths; TYPE_1__* switchers; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_2__ CombiModePrivateData ;

/* Variables and functions */
 int /*<<< orphan*/ * mode_get_icon (int /*<<< orphan*/ ,unsigned int,int) ; 
 TYPE_2__* mode_get_private_data (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static cairo_surface_t * combi_get_icon ( const Mode *sw, unsigned int index, int height )
{
    CombiModePrivateData *pd = mode_get_private_data ( sw );
    for ( unsigned i = 0; i < pd->num_switchers; i++ ) {
        if ( index >= pd->starts[i] && index < ( pd->starts[i] + pd->lengths[i] ) ) {
            cairo_surface_t *icon = mode_get_icon ( pd->switchers[i].mode, index - pd->starts[i], height );
            return icon;
        }
    }
    return NULL;
}