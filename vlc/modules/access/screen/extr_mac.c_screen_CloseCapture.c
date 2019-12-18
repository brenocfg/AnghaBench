#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ p_block; struct TYPE_6__* offscreen_bitmap; scalar_t__ offscreen_context; } ;
typedef  TYPE_1__ screen_data_t ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {TYPE_1__* p_data; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int screen_CloseCapture(demux_t *p_demux)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    screen_data_t *p_data = p_sys->p_data;

    if (p_data->offscreen_context)
        CFRelease(p_data->offscreen_context);

    if (p_data->offscreen_bitmap)
        free(p_data->offscreen_bitmap);

    if (p_data->p_block)
        block_Release(p_data->p_block);

    free(p_data);

    return VLC_SUCCESS;
}