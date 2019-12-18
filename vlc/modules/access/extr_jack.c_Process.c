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
typedef  unsigned int jack_nframes_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {unsigned int i_channels; size_t jack_sample_size; scalar_t__* pp_jack_buffer; int /*<<< orphan*/  p_jack_ringbuffer; int /*<<< orphan*/ * pp_jack_port_input; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ jack_port_get_buffer (int /*<<< orphan*/ ,unsigned int) ; 
 size_t jack_ringbuffer_write (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t jack_ringbuffer_write_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

int Process( jack_nframes_t i_frames, void *p_arg )
{
    demux_t *p_demux = ( demux_t* )p_arg;
    demux_sys_t *p_sys = p_demux->p_sys;

    /* Get and interlace buffers */
    for ( unsigned i = 0; i < p_sys->i_channels ; i++ )
    {
        p_sys->pp_jack_buffer[i] = jack_port_get_buffer(
            p_sys->pp_jack_port_input[i], i_frames );
    }

    /* fill ring buffer with signal */
    for( unsigned j = 0; j < i_frames; j++ )
    {
        for( unsigned i = 0; i <p_sys->i_channels; i++ )
        {
            if( jack_ringbuffer_write_space( p_sys->p_jack_ringbuffer ) <
                p_sys->jack_sample_size ) {
                msg_Err( p_demux, "buffer overflow");
                return 0; // buffer overflow
            }
            size_t i_write = jack_ringbuffer_write( p_sys->p_jack_ringbuffer,
                                                    ( char * ) (p_sys->pp_jack_buffer[i]+j),
                                                    p_sys->jack_sample_size );
            if (i_write != p_sys->jack_sample_size ) {
                msg_Warn( p_demux, "error writing on ring buffer");
            }
        }
    }

    return 0;
}