#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int* pi_offset; int* pi_alpha; int b_auto_crop; unsigned int i_y_top_offset; unsigned int i_y_bottom_offset; int** pi_yuv; int /*<<< orphan*/  b_palette; int /*<<< orphan*/ * p_data; } ;
typedef  TYPE_1__ subpicture_data_t ;
struct TYPE_12__ {unsigned int i_width; unsigned int i_height; } ;
typedef  TYPE_2__ spu_properties_t ;
struct TYPE_13__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_14__ {unsigned int i_spu_size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_15__ {unsigned int i_height; unsigned int i_y; int /*<<< orphan*/  i_x; int /*<<< orphan*/  i_width; } ;

/* Variables and functions */
 unsigned int AddNibble (unsigned int,int /*<<< orphan*/ *,unsigned int*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int,int,int,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,...) ; 
 TYPE_5__* p_spu ; 

__attribute__((used)) static int ParseRLE( decoder_t *p_dec,
                     subpicture_data_t *p_spu_data,
                     const spu_properties_t *p_spu_properties )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    const unsigned int i_width = p_spu_properties->i_width;
    const unsigned int i_height = p_spu_properties->i_height;
    unsigned int i_x, i_y;

    uint16_t *p_dest = p_spu_data->p_data;

    /* The subtitles are interlaced, we need two offsets */
    unsigned int  i_id = 0;                   /* Start on the even SPU layer */
    unsigned int  pi_table[ 2 ];
    unsigned int *pi_offset;

    /* Cropping */
    bool b_empty_top = true;
    unsigned int i_skipped_top = 0, i_skipped_bottom = 0;
    unsigned int i_transparent_code = 0;

    /* Colormap statistics */
    int i_border = -1;
    int stats[4]; stats[0] = stats[1] = stats[2] = stats[3] = 0;

    pi_table[ 0 ] = p_spu_data->pi_offset[ 0 ] << 1;
    pi_table[ 1 ] = p_spu_data->pi_offset[ 1 ] << 1;

    for( i_y = 0 ; i_y < i_height ; i_y++ )
    {
        unsigned int i_code;
        pi_offset = pi_table + i_id;

        for( i_x = 0 ; i_x < i_width ; i_x += i_code >> 2 )
        {
            i_code = 0;
            for( unsigned int i_min = 1; i_min <= 0x40 && i_code < i_min; i_min <<= 2 )
            {
                if( (*pi_offset >> 1) >= p_sys->i_spu_size )
                {
                    msg_Err( p_dec, "out of bounds while reading rle" );
                    return VLC_EGENERIC;
                }
                i_code = AddNibble( i_code, &p_sys->buffer[4], pi_offset );
            }
            if( i_code < 0x0004 )
            {
                /* If the 14 first bits are set to 0, then it's a
                 * new line. We emulate it. */
                i_code |= ( i_width - i_x ) << 2;
            }

            if( ( (i_code >> 2) + i_x + i_y * i_width ) > i_height * i_width )
            {
                msg_Err( p_dec, "out of bounds, %i at (%i,%i) is out of %ix%i",
                         i_code >> 2, i_x, i_y, i_width, i_height );
                return VLC_EGENERIC;
            }

            /* Try to find the border color */
            if( p_spu_data->pi_alpha[ i_code & 0x3 ] != 0x00 )
            {
                i_border = i_code & 0x3;
                stats[i_border] += i_code >> 2;
            }

            /* Auto crop subtitles (a lot more optimized) */
            if( p_spu_data->b_auto_crop )
            {
                if( !i_y )
                {
                    /* We assume that if the first line is transparent, then
                     * it is using the palette index for the
                     * (background) transparent color */
                    if( (i_code >> 2) == i_width &&
                        p_spu_data->pi_alpha[ i_code & 0x3 ] == 0x00 )
                    {
                        i_transparent_code = i_code;
                    }
                    else
                    {
                        p_spu_data->b_auto_crop = false;
                    }
                }

                if( i_code == i_transparent_code )
                {
                    if( b_empty_top )
                    {
                        /* This is a blank top line, we skip it */
                      i_skipped_top++;
                    }
                    else
                    {
                        /* We can't be sure the current lines will be skipped,
                         * so we store the code just in case. */
                      *p_dest++ = i_code;
                      i_skipped_bottom++;
                    }
                }
                else
                {
                    /* We got a valid code, store it */
                    *p_dest++ = i_code;

                    /* Valid code means no blank line */
                    b_empty_top = false;
                    i_skipped_bottom = 0;
                }
            }
            else
            {
                *p_dest++ = i_code;
            }
        }

        /* Check that we didn't go too far */
        if( i_x > i_width )
        {
            msg_Err( p_dec, "i_x overflowed, %i > %i", i_x, i_width );
            return VLC_EGENERIC;
        }

        /* Byte-align the stream */
        if( *pi_offset & 0x1 )
        {
            (*pi_offset)++;
        }

        /* Swap fields */
        i_id = ~i_id & 0x1;
    }

    /* We shouldn't get any padding bytes */
    if( i_y < i_height )
    {
        msg_Err( p_dec, "padding bytes found in RLE sequence" );
        msg_Err( p_dec, "send mail to <sam@zoy.org> if you "
                        "want to help debugging this" );

        /* Skip them just in case */
        while( i_y < i_height )
        {
            *p_dest++ = i_width << 2;
            i_y++;
        }

        return VLC_EGENERIC;
    }

#ifdef DEBUG_SPUDEC
    msg_Dbg( p_dec, "valid subtitle, size: %ix%i, position: %i,%i",
             p_spu->i_width, p_spu->i_height, p_spu->i_x, p_spu->i_y );
#endif

    /* Crop if necessary */
    if( i_skipped_top || i_skipped_bottom )
    {
#ifdef DEBUG_SPUDEC
        int i_y = p_spu->i_y + i_skipped_top;
        int i_height = p_spu->i_height - (i_skipped_top + i_skipped_bottom);
#endif
        p_spu_data->i_y_top_offset = i_skipped_top;
        p_spu_data->i_y_bottom_offset = i_skipped_bottom;
#ifdef DEBUG_SPUDEC
        msg_Dbg( p_dec, "cropped to: %ix%i, position: %i,%i",
                 p_spu->i_width, i_height, p_spu->i_x, i_y );
#endif
    }

    /* Handle color if no palette was found */
    if( !p_spu_data->b_palette )
    {
        int i, i_inner = -1, i_shade = -1;

        /* Set the border color */
        if( i_border != -1 )
        {
            p_spu_data->pi_yuv[i_border][0] = 0x00;
            p_spu_data->pi_yuv[i_border][1] = 0x80;
            p_spu_data->pi_yuv[i_border][2] = 0x80;
            stats[i_border] = 0;
        }

        /* Find the inner colors */
        for( i = 0 ; i < 4 && i_inner == -1 ; i++ )
        {
            if( stats[i] )
            {
                i_inner = i;
            }
        }

        for(       ; i < 4 && i_shade == -1 ; i++ )
        {
            if( stats[i] )
            {
                if( stats[i] > stats[i_inner] )
                {
                    i_shade = i_inner;
                    i_inner = i;
                }
                else
                {
                    i_shade = i;
                }
            }
        }

        /* Set the inner color */
        if( i_inner != -1 )
        {
            p_spu_data->pi_yuv[i_inner][0] = 0xff;
            p_spu_data->pi_yuv[i_inner][1] = 0x80;
            p_spu_data->pi_yuv[i_inner][2] = 0x80;
        }

        /* Set the anti-aliasing color */
        if( i_shade != -1 )
        {
            p_spu_data->pi_yuv[i_shade][0] = 0x80;
            p_spu_data->pi_yuv[i_shade][1] = 0x80;
            p_spu_data->pi_yuv[i_shade][2] = 0x80;
        }

#ifdef DEBUG_SPUDEC
        msg_Dbg( p_dec, "using custom palette (border %i, inner %i, shade %i)",
                 i_border, i_inner, i_shade );
#endif
    }

    return VLC_SUCCESS;
}