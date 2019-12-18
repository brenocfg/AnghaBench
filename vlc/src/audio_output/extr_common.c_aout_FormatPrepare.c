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
struct TYPE_4__ {unsigned int i_channels; int i_bitspersample; int i_bytes_per_frame; int i_frame_length; int /*<<< orphan*/  i_format; } ;
typedef  TYPE_1__ audio_sample_format_t ;

/* Variables and functions */
 int aout_BitsPerSample (int /*<<< orphan*/ ) ; 
 unsigned int aout_FormatNbChannels (TYPE_1__*) ; 

void aout_FormatPrepare( audio_sample_format_t * p_format )
{

    unsigned i_channels = aout_FormatNbChannels( p_format );
    if( i_channels > 0 )
        p_format->i_channels = i_channels;
    p_format->i_bitspersample = aout_BitsPerSample( p_format->i_format );
    if( p_format->i_bitspersample > 0 )
    {
        p_format->i_bytes_per_frame = ( p_format->i_bitspersample / 8 )
                                    * p_format->i_channels;
        p_format->i_frame_length = 1;
    }
}