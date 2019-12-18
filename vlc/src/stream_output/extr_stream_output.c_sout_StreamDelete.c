#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  p_cfg; int /*<<< orphan*/  psz_name; int /*<<< orphan*/ * p_module; scalar_t__ pace_nocontrol; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_out_pace_nocontrol; } ;
typedef  TYPE_2__ sout_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 scalar_t__ vlc_object_parent (TYPE_1__*) ; 

__attribute__((used)) static void sout_StreamDelete( sout_stream_t *p_stream )
{
    sout_instance_t *p_sout = (sout_instance_t *)vlc_object_parent(p_stream);

    msg_Dbg( p_stream, "destroying chain... (name=%s)", p_stream->psz_name );

    p_sout->i_out_pace_nocontrol -= p_stream->pace_nocontrol;

    if( p_stream->p_module != NULL )
        module_unneed( p_stream, p_stream->p_module );

    FREENULL( p_stream->psz_name );

    config_ChainDestroy( p_stream->p_cfg );

    msg_Dbg( p_stream, "destroying chain done" );
    vlc_object_delete(p_stream);
}