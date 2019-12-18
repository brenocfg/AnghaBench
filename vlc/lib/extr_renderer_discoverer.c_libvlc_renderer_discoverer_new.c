#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  event_manager; int /*<<< orphan*/ * p_rd; int /*<<< orphan*/  pp_items; int /*<<< orphan*/  i_items; int /*<<< orphan*/  name; int /*<<< orphan*/  p_object; } ;
typedef  TYPE_1__ libvlc_renderer_discoverer_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_2__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_event_manager_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

libvlc_renderer_discoverer_t *
libvlc_renderer_discoverer_new( libvlc_instance_t *p_inst,
                                const char *psz_name )
{
    size_t len = strlen( psz_name ) + 1;
    libvlc_renderer_discoverer_t *p_lrd = malloc( sizeof(*p_lrd) + len );

    if( unlikely(p_lrd == NULL) )
        return NULL;

    p_lrd->p_object = VLC_OBJECT(p_inst->p_libvlc_int);
    memcpy( p_lrd->name, psz_name, len );
    TAB_INIT( p_lrd->i_items, p_lrd->pp_items );
    p_lrd->p_rd = NULL;
    libvlc_event_manager_init( &p_lrd->event_manager, p_lrd );

    return p_lrd;
}