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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  pf_render; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ filter_t ;
typedef  int /*<<< orphan*/  filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  RenderText ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  g_type_init () ; 
 int /*<<< orphan*/  svg_LoadTemplate (TYPE_1__*) ; 

__attribute__((used)) static int Create( vlc_object_t *p_this )
{
    filter_t *p_filter = ( filter_t * )p_this;

    filter_sys_t *p_sys = calloc( 1, sizeof(*p_sys) );
    if( !p_sys )
        return VLC_ENOMEM;
    p_filter->p_sys = p_sys;

    p_filter->pf_render = RenderText;
    svg_LoadTemplate( p_filter );

#if (GLIB_MAJOR_VERSION < 2 || GLIB_MINOR_VERSION < 36)
    g_type_init( );
#endif

    return VLC_SUCCESS;
}