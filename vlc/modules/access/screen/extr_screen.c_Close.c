#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {TYPE_3__* p_blend; scalar_t__ p_mouse; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_module; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  module_unneed (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 
 int /*<<< orphan*/  screen_CloseCapture (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_3__*) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    screen_CloseCapture( p_demux );
#ifdef SCREEN_MOUSE
    if( p_sys->p_mouse )
        picture_Release( p_sys->p_mouse );
    if( p_sys->p_blend )
    {
        module_unneed( p_sys->p_blend, p_sys->p_blend->p_module );
        vlc_object_delete(p_sys->p_blend);
    }
#endif
    free( p_sys );
}