#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_mux; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
typedef  void sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  sout_mux_t ;
typedef  int /*<<< orphan*/  sout_input_t ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * sout_MuxAddStream (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void *MuxAdd( sout_stream_t *p_stream, const es_format_t *p_fmt )
{
    sout_input_t      *p_input;
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_mux_t *p_mux = p_sys->p_mux;
    assert( p_mux != NULL );

    p_input = sout_MuxAddStream( p_mux, p_fmt );
    if( p_input == NULL )
    {
        msg_Err( p_stream, "cannot add this stream to the muxer" );
        return NULL;
    }

    return (sout_stream_id_sys_t *)p_input;
}