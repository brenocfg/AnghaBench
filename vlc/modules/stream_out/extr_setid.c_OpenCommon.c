#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_del; int /*<<< orphan*/  p_next; } ;
typedef  TYPE_1__ sout_stream_t ;
typedef  int /*<<< orphan*/  sout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Del ; 
 int /*<<< orphan*/  Send ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int OpenCommon( vlc_object_t *p_this )
{
    sout_stream_t     *p_stream = (sout_stream_t*)p_this;
    sout_stream_sys_t *p_sys;

    if( !p_stream->p_next )
    {
        msg_Err( p_stream, "cannot create chain" );
        return VLC_EGENERIC;
    }

    p_sys = malloc( sizeof( sout_stream_sys_t ) );
    if( unlikely( !p_sys ) )
        return VLC_ENOMEM;

    p_stream->pf_del    = Del;
    p_stream->pf_send   = Send;

    p_stream->p_sys     = p_sys;

    return VLC_SUCCESS;
}