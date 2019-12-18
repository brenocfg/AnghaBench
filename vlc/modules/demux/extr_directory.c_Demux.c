#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_4__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; int /*<<< orphan*/  p_input_item; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_POST_SUBNODE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * input_item_node_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_node_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 scalar_t__ vlc_stream_ReadDir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    input_item_node_t *p_node = input_item_node_Create( p_demux->p_input_item );

    if( vlc_stream_ReadDir( p_demux->s, p_node ) )
    {
        msg_Warn( p_demux, "unable to read directory" );
        input_item_node_Delete( p_node );
        return VLC_EGENERIC;
    }

    if (es_out_Control(p_demux->out, ES_OUT_POST_SUBNODE, p_node))
        input_item_node_Delete(p_node);

    return VLC_SUCCESS;
}