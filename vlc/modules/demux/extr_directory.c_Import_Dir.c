#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/ * p_input_item; TYPE_1__* s; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pf_readdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int VLC_EGENERIC ; 
 int VLC_ETIMEOUT ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int Import_Dir( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t *)p_this;

    if( p_demux->s->pf_readdir == NULL )
        return VLC_EGENERIC;
    if( p_demux->p_input_item == NULL )
        return VLC_ETIMEOUT;

    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;

    return VLC_SUCCESS;
}