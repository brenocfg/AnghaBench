#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {int i_attachments; scalar_t__ p_title; int /*<<< orphan*/ * attachments; TYPE_4__* ic; struct TYPE_7__* tracks; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_9__ {struct TYPE_9__* buffer; } ;
struct TYPE_8__ {TYPE_5__* pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_5__*) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_4__**) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (scalar_t__) ; 

void avformat_CloseDemux( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    free( p_sys->tracks );

    if( p_sys->ic )
    {
        if( p_sys->ic->pb )
        {
            av_free( p_sys->ic->pb->buffer );
            av_free( p_sys->ic->pb );
        }
        avformat_close_input( &p_sys->ic );
    }

    for( int i = 0; i < p_sys->i_attachments; i++ )
        vlc_input_attachment_Delete( p_sys->attachments[i] );
    TAB_CLEAN( p_sys->i_attachments, p_sys->attachments);

    if( p_sys->p_title )
        vlc_input_title_Delete( p_sys->p_title );

    free( p_sys );
}