#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_5__ {TYPE_3__* p_array; } ;
struct TYPE_7__ {TYPE_1__ times; scalar_t__ p_xml; scalar_t__ p_reader; scalar_t__ p_es; scalar_t__ p_rootnode; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  tt_node_RecursiveDelete (scalar_t__) ; 
 int /*<<< orphan*/  xml_Delete (scalar_t__) ; 
 int /*<<< orphan*/  xml_ReaderDelete (scalar_t__) ; 

void tt_CloseDemux( vlc_object_t* p_this )
{
    demux_t *p_demux = (demux_t *)p_this;
    demux_sys_t* p_sys = p_demux->p_sys;

    if( p_sys->p_rootnode )
        tt_node_RecursiveDelete( p_sys->p_rootnode );

    if( p_sys->p_es )
        es_out_Del( p_demux->out, p_sys->p_es );

    if( p_sys->p_reader )
        xml_ReaderDelete( p_sys->p_reader );

    if( p_sys->p_xml )
        xml_Delete( p_sys->p_xml );

    free( p_sys->times.p_array );

    free( p_sys );
}