#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i_right_samples; scalar_t__ i_left_samples; } ;
typedef  TYPE_1__ sdi_audio_t ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {int i_width; int i_height; TYPE_1__* p_audios; scalar_t__ p_u; scalar_t__ p_v; scalar_t__ p_y; TYPE_4__* p_current_picture; int /*<<< orphan*/  i_block_size; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_9__ {scalar_t__ p_buffer; } ;

/* Variables and functions */
 int MAX_AUDIOS ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_4__* block_Alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int NewFrame( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    p_sys->p_current_picture = block_Alloc( p_sys->i_block_size );
    if( unlikely( !p_sys->p_current_picture ) )
        return VLC_ENOMEM;
    p_sys->p_y = p_sys->p_current_picture->p_buffer;
    p_sys->p_u = p_sys->p_y + p_sys->i_width * p_sys->i_height;
    p_sys->p_v = p_sys->p_u + p_sys->i_width * p_sys->i_height / 4;

    for ( int i = 0; i < MAX_AUDIOS; i++ )
    {
        sdi_audio_t *p_audio = &p_sys->p_audios[i];
        p_audio->i_left_samples = p_audio->i_right_samples = 0;
    }
    return VLC_SUCCESS;
}