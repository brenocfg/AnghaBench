#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* p_sout; } ;
typedef  TYPE_2__ sout_stream_t ;
struct TYPE_11__ {TYPE_4__* p_mux; int /*<<< orphan*/  p_input; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  sout_access_out_t ;
struct TYPE_12__ {int /*<<< orphan*/ * p_access; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_out_pace_nocontrol; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  sout_AccessOutCanControlPace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_AccessOutDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_MuxDelete (TYPE_4__*) ; 
 int /*<<< orphan*/  sout_MuxDeleteStream (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *_id )
{
    VLC_UNUSED(p_stream);
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    sout_access_out_t *p_access = id->p_mux->p_access;

    sout_MuxDeleteStream( id->p_mux, id->p_input );
    sout_MuxDelete( id->p_mux );
    if( !sout_AccessOutCanControlPace( p_access ) )
        p_stream->p_sout->i_out_pace_nocontrol--;
    sout_AccessOutDelete( p_access );

    free( id );
}