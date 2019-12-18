#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_9__ {size_t i_channels; size_t jack_sample_size; TYPE_3__* p_block_audio; int /*<<< orphan*/  pts; int /*<<< orphan*/  p_jack_ringbuffer; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_10__ {size_t i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; scalar_t__ p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,size_t) ; 
 size_t jack_ringbuffer_read (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t jack_ringbuffer_read_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int) ; 

__attribute__((used)) static block_t *GrabJack( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t *p_block;

    /* read signal from ring buffer */
    size_t i_read = jack_ringbuffer_read_space( p_sys->p_jack_ringbuffer );

    if( i_read < 100 ) /* avoid small read */
    {   /* vlc has too much free time on its hands? */
#undef vlc_tick_sleep
#warning Hmm.... looks wrong
        vlc_tick_sleep(1000);
        return NULL;
    }

    if( p_sys->p_block_audio )
    {
        p_block = p_sys->p_block_audio;
    }
    else
    {
        p_block = block_Alloc( i_read );
    }
    if( !p_block )
    {
        msg_Warn( p_demux, "cannot get block" );
        return 0;
    }

    //Find the previous power of 2, this algo assumes size_t has the same size on all arch
    i_read >>= 1;
    i_read--;
    i_read |= i_read >> 1;
    i_read |= i_read >> 2;
    i_read |= i_read >> 4;
    i_read |= i_read >> 8;
    i_read |= i_read >> 16;
    i_read++;

    i_read = jack_ringbuffer_read( p_sys->p_jack_ringbuffer, ( char * ) p_block->p_buffer, i_read );

    p_block->i_dts = p_block->i_pts = date_Increment( &p_sys->pts,
         i_read/(p_sys->i_channels * p_sys->jack_sample_size) );

    p_sys->p_block_audio = p_block;
    p_block->i_buffer = i_read;
    p_sys->p_block_audio = 0;

    return p_block;
}