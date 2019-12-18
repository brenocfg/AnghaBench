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
struct TYPE_6__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_mux; int /*<<< orphan*/  pf_delstream; int /*<<< orphan*/  pf_addstream; int /*<<< orphan*/  pf_control; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_7__ {int b_header; } ;
typedef  TYPE_2__ sout_mux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddStream ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  DelStream ; 
 int /*<<< orphan*/  Mux ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    sout_mux_t *p_mux = (sout_mux_t*)p_this;
    sout_mux_sys_t  *p_sys;

    msg_Dbg( p_mux, "Dummy/Raw muxer opened" );
    msg_Info( p_mux, "Open" );

    p_mux->pf_control   = Control;
    p_mux->pf_addstream = AddStream;
    p_mux->pf_delstream = DelStream;
    p_mux->pf_mux       = Mux;

    p_mux->p_sys = p_sys = malloc( sizeof( sout_mux_sys_t ) );
    if( !p_sys )
        return VLC_ENOMEM;
    p_sys->b_header      = true;

    return VLC_SUCCESS;
}