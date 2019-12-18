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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {int i_seekpoint; int i_attachments; int i_title_seekpoints; scalar_t__ p_meta; scalar_t__ p_packetizer; struct TYPE_8__** pp_title_seekpoints; struct TYPE_8__** attachments; struct TYPE_8__** seekpoint; scalar_t__ p_current_block; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,TYPE_2__**) ; 
 int /*<<< orphan*/  block_Release (scalar_t__) ; 
 int /*<<< orphan*/  demux_PacketizerDestroy (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_meta_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_seekpoint_Delete (TYPE_2__*) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_sys->p_current_block )
        block_Release( p_sys->p_current_block );

    for( int i = 0; i < p_sys->i_seekpoint; i++ )
        free(p_sys->seekpoint[i]);
    TAB_CLEAN( p_sys->i_seekpoint, p_sys->seekpoint );

    for( int i = 0; i < p_sys->i_attachments; i++ )
        vlc_input_attachment_Delete( p_sys->attachments[i] );
    TAB_CLEAN( p_sys->i_attachments, p_sys->attachments);

    for( int i = 0; i < p_sys->i_title_seekpoints; i++ )
        vlc_seekpoint_Delete( p_sys->pp_title_seekpoints[i] );
    TAB_CLEAN( p_sys->i_title_seekpoints, p_sys->pp_title_seekpoints );

    /* Delete the decoder */
    if( p_sys->p_packetizer )
        demux_PacketizerDestroy( p_sys->p_packetizer );

    if( p_sys->p_meta )
        vlc_meta_Delete( p_sys->p_meta );
    free( p_sys );
}