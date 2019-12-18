#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {TYPE_1__* p_picture; } ;
typedef  TYPE_2__ subpicture_region_t ;
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_12__ {int i_height; int i_width; scalar_t__ i_image_offset; } ;
typedef  TYPE_4__ decoder_sys_t ;
typedef  int /*<<< orphan*/  bs_t ;
struct TYPE_13__ {scalar_t__ i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_9__ {int* Y_PIXELS; int Y_PITCH; } ;

/* Variables and functions */
 int __MIN (int,int) ; 
 int /*<<< orphan*/  bs_align (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void RenderImage( decoder_t *p_dec, block_t *p_data,
                         subpicture_region_t *p_region )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    uint8_t *p_dest = p_region->p_picture->Y_PIXELS;
    int i_field;            /* The subtitles are interlaced */
    int i_row, i_column;    /* scanline row/column number */
    uint8_t i_color, i_count;
    bs_t bs;

    bs_init( &bs, p_data->p_buffer + p_sys->i_image_offset,
             p_data->i_buffer - p_sys->i_image_offset );

    for( i_field = 0; i_field < 2; i_field++ )
    {
        for( i_row = i_field; i_row < p_sys->i_height; i_row += 2 )
        {
            for( i_column = 0; i_column < p_sys->i_width; i_column++ )
            {
                uint8_t i_val = bs_read( &bs, 4 );

                if( i_val == 0 )
                {
                    /* Fill the rest of the line with next color */
                    i_color = bs_read( &bs, 4 );

                    memset( &p_dest[i_row * p_region->p_picture->Y_PITCH +
                                    i_column], i_color,
                            p_sys->i_width - i_column );
                    i_column = p_sys->i_width;
                    continue;
                }
                else
                {
                    /* Normal case: get color and repeat count */
                    i_count = (i_val >> 2);
                    i_color = i_val & 0x3;

                    i_count = __MIN( i_count, p_sys->i_width - i_column );

                    memset( &p_dest[i_row * p_region->p_picture->Y_PITCH +
                                    i_column], i_color, i_count );
                    i_column += i_count - 1;
                    continue;
                }
            }

            bs_align( &bs );
        }
    }
}