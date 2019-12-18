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
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* _get_icon ) (TYPE_1__ const*,unsigned int,int) ;} ;
typedef  TYPE_1__ Mode ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__ const*,unsigned int,int) ; 

cairo_surface_t * mode_get_icon ( const Mode *mode, unsigned int selected_line, int height )
{
    g_assert ( mode != NULL );

    if ( mode->_get_icon != NULL ) {
        return mode->_get_icon ( mode, selected_line, height );
    }
    else {
        return NULL;
    }
}