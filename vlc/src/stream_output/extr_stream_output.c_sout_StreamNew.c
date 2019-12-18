#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* psz_name; int pace_nocontrol; int /*<<< orphan*/ * p_cfg; int /*<<< orphan*/  p_module; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/ * pf_control; int /*<<< orphan*/ * pf_flush; struct TYPE_11__* p_next; TYPE_2__* p_sout; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_12__ {int i_out_pace_nocontrol; } ;
typedef  TYPE_2__ sout_instance_t ;
typedef  int /*<<< orphan*/  config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  module_need (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  sout_StreamDelete (TYPE_1__*) ; 
 TYPE_1__* vlc_custom_create (TYPE_2__*,int,char*) ; 

__attribute__((used)) static sout_stream_t *sout_StreamNew( sout_instance_t *p_sout, char *psz_name,
                               config_chain_t *p_cfg, sout_stream_t *p_next)
{
    sout_stream_t *p_stream;

    assert(psz_name);

    p_stream = vlc_custom_create( p_sout, sizeof( *p_stream ), "stream out" );
    if( !p_stream )
        return NULL;

    p_stream->p_sout   = p_sout;
    p_stream->psz_name = psz_name;
    p_stream->p_cfg    = p_cfg;
    p_stream->p_next   = p_next;
    p_stream->pf_flush = NULL;
    p_stream->pf_control = NULL;
    p_stream->pace_nocontrol = false;
    p_stream->p_sys = NULL;

    msg_Dbg( p_sout, "stream=`%s'", p_stream->psz_name );

    p_stream->p_module =
        module_need( p_stream, "sout stream", p_stream->psz_name, true );

    if( !p_stream->p_module )
    {
        /* those must be freed by the caller if creation failed */
        p_stream->psz_name = NULL;
        p_stream->p_cfg = NULL;

        sout_StreamDelete( p_stream );
        return NULL;
    }

    p_sout->i_out_pace_nocontrol += p_stream->pace_nocontrol;
    return p_stream;
}