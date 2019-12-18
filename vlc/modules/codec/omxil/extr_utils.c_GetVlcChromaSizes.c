#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_2__ {scalar_t__ i_codec; scalar_t__ i_fourcc; unsigned int i_size_mul; unsigned int i_line_mul; unsigned int i_line_chroma_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
 TYPE_1__* chroma_format_table ; 
 scalar_t__ vlc_fourcc_GetCodec (int /*<<< orphan*/ ,scalar_t__) ; 

int GetVlcChromaSizes( vlc_fourcc_t i_fourcc,
                       unsigned int width, unsigned int height,
                       unsigned int *size, unsigned int *pitch,
                       unsigned int *chroma_pitch_div )
{
    unsigned int i;

    i_fourcc = vlc_fourcc_GetCodec( VIDEO_ES, i_fourcc );

    for( i = 0; chroma_format_table[i].i_codec != 0; i++ )
        if( chroma_format_table[i].i_fourcc == i_fourcc ) break;

    /* Align on macroblock boundary */
    width = (width + 15) & ~0xF;
    height = (height + 15) & ~0xF;

    if( size ) *size = width * height * chroma_format_table[i].i_size_mul / 2;
    if( pitch ) *pitch = width * chroma_format_table[i].i_line_mul;
    if( chroma_pitch_div )
        *chroma_pitch_div = chroma_format_table[i].i_line_chroma_div;
    return !!chroma_format_table[i].i_codec;
}