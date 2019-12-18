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
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {unsigned int i_buffers; int /*<<< orphan*/ * pp_buffers; int /*<<< orphan*/  i_fd; int /*<<< orphan*/  i_buffer_size; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  StopDecode (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CloseCapture( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    StopDecode( p_demux );
    for ( unsigned int i = 0; i < p_sys->i_buffers; i++ )
        munmap( p_sys->pp_buffers[i], p_sys->i_buffer_size );
    vlc_close( p_sys->i_fd );
    free( p_sys->pp_buffers );
}