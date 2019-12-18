#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int i_height; int i_width; int /*<<< orphan*/ * p_pixbuf; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ dvbsub_region_t ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int /*<<< orphan*/  bs_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dvbsub_pdata2bpp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dvbsub_pdata4bpp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dvbsub_pdata8bpp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dvbsub_render_pdata( decoder_t *p_dec, dvbsub_region_t *p_region,
                                 int i_x, int i_y,
                                 uint8_t *p_field, int i_field )
{
    uint8_t *p_pixbuf;
    int i_offset = 0;
    bs_t bs;

    /* Sanity check */
    if( !p_region->p_pixbuf )
    {
        msg_Err( p_dec, "region %i has no pixel buffer!", p_region->i_id );
        return;
    }
    if( i_y < 0 || i_x < 0 || i_y >= p_region->i_height ||
        i_x >= p_region->i_width )
    {
        msg_Dbg( p_dec, "invalid offset (%i,%i)", i_x, i_y );
        return;
    }

    p_pixbuf = p_region->p_pixbuf + i_y * p_region->i_width;
    bs_init( &bs, p_field, i_field );

    while( !bs_eof( &bs ) )
    {
        /* Sanity check */
        if( i_y >= p_region->i_height ) return;

        switch( bs_read( &bs, 8 ) )
        {
        case 0x10:
            dvbsub_pdata2bpp( &bs, p_pixbuf + i_x, p_region->i_width - i_x,
                              &i_offset );
            break;

        case 0x11:
            dvbsub_pdata4bpp( &bs, p_pixbuf + i_x, p_region->i_width - i_x,
                              &i_offset );
            break;

        case 0x12:
            dvbsub_pdata8bpp( &bs, p_pixbuf + i_x, p_region->i_width - i_x,
                              &i_offset );
            break;

        case 0x20:
        case 0x21:
        case 0x22:
            /* We don't use map tables */
            break;

        case 0xf0: /* End of line code */
            p_pixbuf += 2*p_region->i_width;
            i_offset = 0; i_y += 2;
            break;
        }
    }
}