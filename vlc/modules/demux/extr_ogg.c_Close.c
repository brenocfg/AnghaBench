#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {scalar_t__ p_old_stream; int /*<<< orphan*/  oy; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Ogg_EndOfStream (TYPE_1__*) ; 
 int /*<<< orphan*/  Ogg_LogicalStreamDelete (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_sync_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t *)p_this;
    demux_sys_t *p_sys = p_demux->p_sys  ;

    /* Cleanup the bitstream parser */
    ogg_sync_clear( &p_sys->oy );

    Ogg_EndOfStream( p_demux );

    if( p_sys->p_old_stream )
        Ogg_LogicalStreamDelete( p_demux, p_sys->p_old_stream );

    free( p_sys );
}