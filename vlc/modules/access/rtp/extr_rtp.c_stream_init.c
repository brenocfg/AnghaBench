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
struct TYPE_5__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {void* chained_demux; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 void* vlc_demux_chained_New (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *stream_init (demux_t *demux, const char *name)
{
    demux_sys_t *p_sys = demux->p_sys;

    if (p_sys->chained_demux != NULL)
        return NULL;
    p_sys->chained_demux = vlc_demux_chained_New(VLC_OBJECT(demux), name,
                                                 demux->out);
    return p_sys->chained_demux;
}