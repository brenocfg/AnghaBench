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
struct TYPE_8__ {TYPE_3__* p_sys; int /*<<< orphan*/  pf_mux; int /*<<< orphan*/  pf_delstream; int /*<<< orphan*/  pf_addstream; int /*<<< orphan*/  pf_control; } ;
typedef  TYPE_2__ sout_mux_t ;
struct TYPE_7__ {int i_entry_max; int /*<<< orphan*/  entry; scalar_t__ i_entry_count; } ;
struct TYPE_9__ {int i_stream_video; int b_write_header; TYPE_1__ idx1; scalar_t__ i_movi_size; scalar_t__ i_streams; } ;
typedef  TYPE_3__ sout_mux_sys_t ;
typedef  int /*<<< orphan*/  avi_idx1_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddStream ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  DelStream ; 
 int /*<<< orphan*/  Mux ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    sout_mux_t      *p_mux = (sout_mux_t*)p_this;
    sout_mux_sys_t  *p_sys;

    msg_Dbg( p_mux, "AVI muxer opened" );

    p_sys = malloc( sizeof( sout_mux_sys_t ) );
    if( !p_sys )
        return VLC_ENOMEM;
    p_sys->i_streams = 0;
    p_sys->i_stream_video = -1;
    p_sys->i_movi_size = 0;

    p_sys->idx1.i_entry_count = 0;
    p_sys->idx1.i_entry_max = 10000;
    p_sys->idx1.entry = calloc( p_sys->idx1.i_entry_max,
                                sizeof( avi_idx1_entry_t ) );
    if( !p_sys->idx1.entry )
    {
        free( p_sys );
        return VLC_ENOMEM;
    }
    p_sys->b_write_header = true;


    p_mux->pf_control   = Control;
    p_mux->pf_addstream = AddStream;
    p_mux->pf_delstream = DelStream;
    p_mux->pf_mux       = Mux;
    p_mux->p_sys        = p_sys;

    return VLC_SUCCESS;
}