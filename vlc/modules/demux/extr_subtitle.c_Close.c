#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_6__ {TYPE_4__* psz_header; } ;
struct TYPE_7__ {size_t i_count; TYPE_4__* p_array; } ;
struct TYPE_9__ {TYPE_1__ props; TYPE_2__ subtitles; struct TYPE_9__* psz_text; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    for( size_t i = 0; i < p_sys->subtitles.i_count; i++ )
        free( p_sys->subtitles.p_array[i].psz_text );
    free( p_sys->subtitles.p_array );
    free( p_sys->props.psz_header );

    free( p_sys );
}