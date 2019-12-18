#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int line; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ vbi_sliced ;
typedef  int uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_11__ {int i_telx_count; int /*<<< orphan*/  p_es_telx; int /*<<< orphan*/  i_next_date; int /*<<< orphan*/  p_telx_buffer; int /*<<< orphan*/  rd_telx; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_12__ {int* p_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_4__* block_Alloc (int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int vbi_raw_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int vbi_rev8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DecodeTelx( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    vbi_sliced p_sliced[p_sys->i_telx_count * 2];
    int i_nb_slices = vbi_raw_decode( &p_sys->rd_telx, p_sys->p_telx_buffer,
                                      p_sliced );

    if ( i_nb_slices )
    {
        /* 3, 7, 11, 15, etc. */
        int i_nb_slices_rounded = 3 + (i_nb_slices / 4) * 4;
        int i;
        uint8_t *p;
        block_t *p_block = block_Alloc( 1 + i_nb_slices_rounded * 46 );
        if( unlikely( !p_block ) )
            return VLC_ENOMEM;
        p_block->p_buffer[0] = 0x10; /* FIXME ? data_identifier */
        p = p_block->p_buffer + 1;

        for ( i = 0; i < i_nb_slices; i++ )
        {
            int i_line = p_sliced[i].line;
            p[0] = 0x3; /* FIXME data_unit_id == subtitles */
            p[1] = 0x2c; /* data_unit_length */
            /* reserved | field_parity (kind of inverted) | line */
            p[2] = 0xc0 | (i_line > 313 ? 0 : 0x20) | (i_line % 313);
            p[3] = 0xe4; /* framing code */
            for ( int j = 0; j < 42; j++ )
                p[4 + j] = vbi_rev8( p_sliced[i].data[j] );
            p += 46;
        }

        /* Let's stuff */
        for ( ; i < i_nb_slices_rounded; i++ )
        {
            p[0] = 0xff;
            p[1] = 0x2c;
            memset( p + 2, 0xff, 44 );
            p += 46;
        }

        p_block->i_dts = p_block->i_pts = p_sys->i_next_date;
        es_out_Send( p_demux->out, p_sys->p_es_telx, p_block );
    }
    return VLC_SUCCESS;
}