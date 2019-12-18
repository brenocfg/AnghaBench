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
struct TYPE_7__ {int /*<<< orphan*/  p_next; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {int i_id; struct TYPE_8__** id; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
typedef  TYPE_2__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,TYPE_2__**) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sout_StreamIdDel (int /*<<< orphan*/ ,TYPE_2__**) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_stream_t     *p_stream = (sout_stream_t*)p_this;
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    int i;

    for( i = 0; i < p_sys->i_id; i++ )
    {
        sout_stream_id_sys_t *id = p_sys->id[i];

        sout_StreamIdDel( p_stream->p_next, id->id );
        es_format_Clean( &id->fmt );
        free( id );
    }
    TAB_CLEAN( p_sys->i_id, p_sys->id );

    free( p_sys );
}