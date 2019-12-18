#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_del; int /*<<< orphan*/  pf_add; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_stream_start; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ sout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Add ; 
 int /*<<< orphan*/  Del ; 
 int /*<<< orphan*/  Send ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * var_InheritAddress (TYPE_1__*,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    sout_stream_t *p_stream = (sout_stream_t*)p_this;
    sout_stream_sys_t *p_sys = malloc(sizeof(sout_stream_sys_t));
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    p_stream->pf_add  = Add;
    p_stream->pf_del  = Del;
    p_stream->pf_send = Send;
    p_stream->p_sys = p_sys;

    p_sys->data = var_InheritAddress(p_stream, "sout-description-data");
    if (p_sys->data == NULL)
    {
        msg_Err(p_stream, "Missing data: the description stream output is "
                "not meant to be used without special setup from the core");
        free(p_sys);
        return VLC_EGENERIC;
    }
    p_sys->i_stream_start = VLC_TICK_INVALID;

    return VLC_SUCCESS;
}