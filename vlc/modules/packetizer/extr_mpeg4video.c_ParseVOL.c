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
typedef  int uint8_t ;
struct TYPE_7__ {void* i_height; void* i_width; } ;
struct TYPE_8__ {TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_10__ {int i_fps_num; void* i_fps_den; } ;
typedef  TYPE_4__ decoder_sys_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int*,int) ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bs_read1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int vlc_log2 (int) ; 

__attribute__((used)) static int ParseVOL( decoder_t *p_dec, es_format_t *fmt,
                     uint8_t *p_vol, int i_vol )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    int i_vo_ver_id, i_ar, i_shape;
    bs_t s;

    for( ;; )
    {
        if( i_vol <= 5 )
            return VLC_EGENERIC;

        if( p_vol[0] == 0x00 && p_vol[1] == 0x00 && p_vol[2] == 0x01 &&
            p_vol[3] >= 0x20 && p_vol[3] <= 0x2f ) break;

        p_vol++; i_vol--;
    }

    bs_init( &s, &p_vol[4], i_vol - 4 );

    bs_skip( &s, 1 );   /* random access */
    bs_skip( &s, 8 );   /* vo_type */
    if( bs_read1( &s ) )
    {
        i_vo_ver_id = bs_read( &s, 4 );
        bs_skip( &s, 3 );
    }
    else
    {
        i_vo_ver_id = 1;
    }
    i_ar = bs_read( &s, 4 );
    if( i_ar == 0xf )
    {
        bs_skip( &s, 8 );  /* ar_width */
        bs_skip( &s, 8 );  /* ar_height */
    }
    if( bs_read1( &s ) )
    {
        /* vol control parameter */
        bs_skip( &s, 2 ); /* chroma_format */
        bs_read1( &s ); /* low_delay */

        if( bs_read1( &s ) )
        {
            bs_skip( &s, 16 );
            bs_skip( &s, 16 );
            bs_skip( &s, 16 );
            bs_skip( &s, 3 );
            bs_skip( &s, 11 );
            bs_skip( &s, 1 );
            bs_skip( &s, 16 );
        }
    }
    /* shape 0->RECT, 1->BIN, 2->BIN_ONLY, 3->GRAY */
    i_shape = bs_read( &s, 2 );
    if( i_shape == 3 && i_vo_ver_id != 1 )
    {
        bs_skip( &s, 4 );
    }

    if( !bs_read1( &s ) ) return VLC_EGENERIC; /* Marker */

    p_sys->i_fps_num = bs_read( &s, 16 ); /* Time increment resolution*/
    if( !p_sys->i_fps_num ) p_sys->i_fps_num = 1;

    if( !bs_read1( &s ) ) return VLC_EGENERIC; /* Marker */

    if( bs_read1( &s ) )
    {
        int i_time_increment_bits = vlc_log2( p_sys->i_fps_num - 1 ) + 1;

        if( i_time_increment_bits < 1 ) i_time_increment_bits = 1;

        p_sys->i_fps_den = bs_read( &s, i_time_increment_bits );
    }
    if( i_shape == 0 )
    {
        bs_skip( &s, 1 );
        fmt->video.i_width = bs_read( &s, 13 );
        bs_skip( &s, 1 );
        fmt->video.i_height= bs_read( &s, 13 );
        bs_skip( &s, 1 );
    }

    return VLC_SUCCESS;
}