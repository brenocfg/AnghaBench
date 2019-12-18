#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct block_sys_t {int /*<<< orphan*/  self; scalar_t__ hbmp; } ;
struct TYPE_11__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; scalar_t__ biClrImportant; scalar_t__ biClrUsed; scalar_t__ biYPelsPerMeter; scalar_t__ biXPelsPerMeter; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_17__ {TYPE_1__ bmiHeader; } ;
struct TYPE_14__ {int i_fragment_size; scalar_t__ hgdi_backup; int /*<<< orphan*/  hdc_dst; TYPE_9__ bmi; scalar_t__ p_block; scalar_t__ i_fragment; } ;
typedef  TYPE_4__ screen_data_t ;
struct TYPE_15__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_12__ {int i_width; int i_height; int i_bits_per_pixel; } ;
struct TYPE_13__ {TYPE_2__ video; } ;
struct TYPE_16__ {int f_fps; TYPE_3__ fmt; int /*<<< orphan*/  i_incr; TYPE_4__* p_data; } ;
typedef  TYPE_6__ demux_sys_t ;
typedef  int /*<<< orphan*/  block_t ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CaptureBlockCallbacks ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  block_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 struct block_sys_t* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 
 int var_CreateGetInteger (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  vlc_tick_rate_duration (int) ; 

__attribute__((used)) static block_t *CaptureBlockNew( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    screen_data_t *p_data = p_sys->p_data;
    struct block_sys_t *p_block;
    void *p_buffer;
    int i_buffer;
    HBITMAP hbmp;

    if( p_data->bmi.bmiHeader.biSize == 0 )
    {
        int i_val;
        /* Create the bitmap info header */
        p_data->bmi.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
        p_data->bmi.bmiHeader.biWidth         = p_sys->fmt.video.i_width;
        p_data->bmi.bmiHeader.biHeight        = - p_sys->fmt.video.i_height;
        p_data->bmi.bmiHeader.biPlanes        = 1;
        p_data->bmi.bmiHeader.biBitCount      = p_sys->fmt.video.i_bits_per_pixel;
        p_data->bmi.bmiHeader.biCompression   = BI_RGB;
        p_data->bmi.bmiHeader.biSizeImage     = 0;
        p_data->bmi.bmiHeader.biXPelsPerMeter = 0;
        p_data->bmi.bmiHeader.biYPelsPerMeter = 0;
        p_data->bmi.bmiHeader.biClrUsed       = 0;
        p_data->bmi.bmiHeader.biClrImportant  = 0;

        i_val = var_CreateGetInteger( p_demux, "screen-fragment-size" );
        p_data->i_fragment_size = i_val > 0 ? i_val : (int)p_sys->fmt.video.i_height;
        p_data->i_fragment_size = i_val > (int)p_sys->fmt.video.i_height ?
                                            (int)p_sys->fmt.video.i_height :
                                            p_data->i_fragment_size;
        p_sys->f_fps *= (p_sys->fmt.video.i_height/p_data->i_fragment_size);
        p_sys->i_incr = vlc_tick_rate_duration( p_sys->f_fps );
        p_data->i_fragment = 0;
        p_data->p_block = 0;
    }


    /* Create the bitmap storage space */
    hbmp = CreateDIBSection( p_data->hdc_dst, &p_data->bmi, DIB_RGB_COLORS,
                             &p_buffer, NULL, 0 );
    if( !hbmp || !p_buffer )
    {
        msg_Err( p_demux, "cannot create bitmap" );
        goto error;
    }

    /* Select the bitmap into the compatible DC */
    if( !p_data->hgdi_backup )
        p_data->hgdi_backup = SelectObject( p_data->hdc_dst, hbmp );
    else
        SelectObject( p_data->hdc_dst, hbmp );

    if( !p_data->hgdi_backup )
    {
        msg_Err( p_demux, "cannot select bitmap" );
        goto error;
    }

    /* Build block */
    if( !(p_block = malloc( sizeof( struct block_sys_t ) )) )
        goto error;

    /* Fill all fields */
    int i_stride =
        ( ( ( ( p_sys->fmt.video.i_width * p_sys->fmt.video.i_bits_per_pixel ) + 31 ) & ~31 ) >> 3 );
    i_buffer = i_stride * p_sys->fmt.video.i_height;
    block_Init( &p_block->self, &CaptureBlockCallbacks, p_buffer, i_buffer );
    p_block->hbmp            = hbmp;

    return &p_block->self;

error:
    if( hbmp ) DeleteObject( hbmp );
    return NULL;
}