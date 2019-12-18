#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  color_range; int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; } ;
struct TYPE_12__ {TYPE_3__ video; } ;
struct TYPE_9__ {scalar_t__ primaries; } ;
struct TYPE_10__ {TYPE_1__ video; } ;
struct TYPE_13__ {TYPE_4__ fmt_out; TYPE_2__ fmt_in; } ;
typedef  TYPE_5__ decoder_t ;
typedef  int /*<<< orphan*/  bs_t ;
struct TYPE_14__ {scalar_t__ i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 scalar_t__ COLOR_PRIMARIES_UNDEF ; 
 int /*<<< orphan*/  COLOR_RANGE_FULL ; 
 int /*<<< orphan*/  COLOR_RANGE_LIMITED ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bs_read1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iso_23001_8_cp_to_vlc_primaries (int) ; 
 int /*<<< orphan*/  iso_23001_8_mc_to_vlc_coeffs (int) ; 
 int /*<<< orphan*/  iso_23001_8_tc_to_vlc_xfer (int) ; 

__attribute__((used)) static int ParseVO( decoder_t *p_dec, block_t *p_vo )
{
    bs_t s;
    bs_init( &s, &p_vo->p_buffer[4], p_vo->i_buffer - 4 );
    if( bs_read1( &s ) )
        bs_skip( &s, 7 );

    const uint8_t visual_object_type = bs_read( &s, 4 );
    if( visual_object_type == 1 /* video ID */ ||
        visual_object_type == 2 /* still texture ID */ )
    {
        uint8_t colour_primaries = 1;
        uint8_t colour_xfer = 1;
        uint8_t colour_matrix_coeff = 1;
        uint8_t full_range = 0;
        if( bs_read1( &s ) ) /* video_signal_type */
        {
            bs_read( &s, 3 );
            full_range = bs_read( &s, 1 );
            if( bs_read( &s, 1 ) ) /* colour description */
            {
                colour_primaries = bs_read( &s, 8 );
                colour_xfer = bs_read( &s, 8 );
                colour_matrix_coeff = bs_read( &s, 8 );
            }
        }

        if( p_dec->fmt_in.video.primaries == COLOR_PRIMARIES_UNDEF )
        {
            p_dec->fmt_out.video.primaries = iso_23001_8_cp_to_vlc_primaries( colour_primaries );
            p_dec->fmt_out.video.transfer = iso_23001_8_tc_to_vlc_xfer( colour_xfer );
            p_dec->fmt_out.video.space = iso_23001_8_mc_to_vlc_coeffs( colour_matrix_coeff );
            p_dec->fmt_out.video.color_range = full_range ? COLOR_RANGE_FULL : COLOR_RANGE_LIMITED;
        }
    }

    return VLC_SUCCESS;
}