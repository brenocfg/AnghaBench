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
struct TYPE_7__ {int /*<<< orphan*/  p_next; scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  pp_es; int /*<<< orphan*/  i_es_num; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/ * id; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  sout_StreamIdDel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *_p_es )
{
    sout_stream_sys_t *p_sys = (sout_stream_sys_t *)p_stream->p_sys;
    sout_stream_id_sys_t *p_es = (sout_stream_id_sys_t *)_p_es;

    if( p_es->id != NULL )
        sout_StreamIdDel( p_stream->p_next, p_es->id );

    TAB_REMOVE( p_sys->i_es_num, p_sys->pp_es, p_es );
    es_format_Clean( &p_es->fmt );
    free( p_es );
}