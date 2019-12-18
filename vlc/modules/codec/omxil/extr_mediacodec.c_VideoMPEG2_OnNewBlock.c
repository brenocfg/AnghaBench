#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_7__ {int i_mpeg_dar_num; int i_mpeg_dar_den; } ;
struct TYPE_9__ {TYPE_1__ video; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_10__ {int i_buffer; int* p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */

__attribute__((used)) static int VideoMPEG2_OnNewBlock(decoder_t *p_dec, block_t **pp_block)
{
    if (pp_block == NULL || (*pp_block)->i_buffer <= 7)
        return 1;

    decoder_sys_t *p_sys = p_dec->p_sys;
    const int startcode = (*pp_block)->p_buffer[3];

    /* DAR aspect ratio from the DVD MPEG2 standard */
    static const int mpeg2_aspect[16][2] =
    {
        {0,0}, /* reserved */
        {0,0}, /* DAR = 0:0 will result in SAR = 1:1 */
        {4,3}, {16,9}, {221,100},
        /* reserved */
        {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
        {0,0}, {0,0}
    };

    if (startcode == 0xB3 /* SEQUENCE_HEADER_STARTCODE */)
    {
        int mpeg_dar_code = (*pp_block)->p_buffer[7] >> 4;

        if (mpeg_dar_code >= 16)
            return 0;

        p_sys->video.i_mpeg_dar_num = mpeg2_aspect[mpeg_dar_code][0];
        p_sys->video.i_mpeg_dar_den = mpeg2_aspect[mpeg_dar_code][1];
    }

    return 1;
}