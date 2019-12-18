#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {TYPE_3__** track; int /*<<< orphan*/ * meta; int /*<<< orphan*/ * p_fp; int /*<<< orphan*/ * p_root; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {struct TYPE_10__* p_fmt; scalar_t__ p_es; } ;
typedef  TYPE_3__ asf_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_FreeObjectRoot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FlushQueues (TYPE_1__*) ; 
 int MAX_ASF_TRACKS ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DemuxEnd( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_sys->p_root )
    {
        ASF_FreeObjectRoot( p_demux->s, p_sys->p_root );
        p_sys->p_root = NULL;
        p_sys->p_fp = NULL;
    }
    if( p_sys->meta )
    {
        vlc_meta_Delete( p_sys->meta );
        p_sys->meta = NULL;
    }

    FlushQueues( p_demux );

    for( int i = 0; i < MAX_ASF_TRACKS; i++ )
    {
        asf_track_t *tk = p_sys->track[i];

        if( tk )
        {
            if( tk->p_es )
            {
                es_out_Del( p_demux->out, tk->p_es );
            }
            if ( tk->p_fmt )
            {
                es_format_Clean( tk->p_fmt );
                free( tk->p_fmt );
            }
            free( tk );
        }
        p_sys->track[i] = 0;
    }
}