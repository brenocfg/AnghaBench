#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int i_planes; int /*<<< orphan*/  date; TYPE_4__* p; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_23__ {int i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
struct TYPE_24__ {TYPE_1__ video; } ;
struct TYPE_28__ {TYPE_2__ fmt_in; TYPE_7__* p_sys; } ;
typedef  TYPE_6__ encoder_t ;
struct TYPE_31__ {int image_height; int input_components; int next_scanline; int max_v_samp_factor; TYPE_3__* comp_info; int /*<<< orphan*/  do_fancy_downsampling; int /*<<< orphan*/  raw_data_in; int /*<<< orphan*/  in_color_space; int /*<<< orphan*/  image_width; } ;
struct TYPE_29__ {TYPE_9__ p_jpeg; int /*<<< orphan*/  i_quality; int /*<<< orphan*/  setjmp_buffer; int /*<<< orphan*/  i_blocksize; } ;
typedef  TYPE_7__ encoder_sys_t ;
struct TYPE_30__ {unsigned long i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_8__ block_t ;
struct TYPE_26__ {int i_pitch; int /*<<< orphan*/ **************** p_pixels; } ;
struct TYPE_25__ {int v_samp_factor; } ;
typedef  int /*<<< orphan*/  JSAMPROW ;
typedef  int /*<<< orphan*/ ********** JSAMPIMAGE ;
typedef  int /*<<< orphan*/  JSAMPARRAY ;

/* Variables and functions */
 int DCTSIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JCS_YCbCr ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_8__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_8__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **********) ; 
 int /*<<< orphan*/  jpeg_create_compress (TYPE_9__*) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (TYPE_9__*) ; 
 int /*<<< orphan*/  jpeg_finish_compress (TYPE_9__*) ; 
 int /*<<< orphan*/  jpeg_mem_dest (TYPE_9__*,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  jpeg_set_colorspace (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_set_defaults (TYPE_9__*) ; 
 int /*<<< orphan*/  jpeg_set_quality (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_start_compress (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_write_raw_data (TYPE_9__*,int /*<<< orphan*/ **********,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 void* vlc_alloc (int,int) ; 

__attribute__((used)) static block_t *EncodeBlock(encoder_t *p_enc, picture_t *p_pic)
{
    encoder_sys_t *p_sys = p_enc->p_sys;

    if (unlikely(!p_pic))
    {
        return NULL;
    }
    block_t *p_block = block_Alloc(p_sys->i_blocksize);
    if (p_block == NULL)
    {
        return NULL;
    }

    JSAMPIMAGE p_row_pointers = NULL;
    unsigned long size = p_block->i_buffer;

    /* libjpeg longjmp's there in case of error */
    if (setjmp(p_sys->setjmp_buffer))
    {
        goto error;
    }

    jpeg_create_compress(&p_sys->p_jpeg);
    jpeg_mem_dest(&p_sys->p_jpeg, &p_block->p_buffer, &size);

    p_sys->p_jpeg.image_width = p_enc->fmt_in.video.i_visible_width;
    p_sys->p_jpeg.image_height = p_enc->fmt_in.video.i_visible_height;
    p_sys->p_jpeg.input_components = 3;
    p_sys->p_jpeg.in_color_space = JCS_YCbCr;

    jpeg_set_defaults(&p_sys->p_jpeg);
    jpeg_set_colorspace(&p_sys->p_jpeg, JCS_YCbCr);

    p_sys->p_jpeg.raw_data_in = TRUE;
#if JPEG_LIB_VERSION >= 70
    p_sys->p_jpeg.do_fancy_downsampling = FALSE;
#endif

    jpeg_set_quality(&p_sys->p_jpeg, p_sys->i_quality, TRUE);

    jpeg_start_compress(&p_sys->p_jpeg, TRUE);

    /* Encode picture */
    p_row_pointers = vlc_alloc(p_pic->i_planes, sizeof(JSAMPARRAY));
    if (p_row_pointers == NULL)
    {
        goto error;
    }

    for (int i = 0; i < p_pic->i_planes; i++)
    {
        p_row_pointers[i] = vlc_alloc(p_sys->p_jpeg.comp_info[i].v_samp_factor, sizeof(JSAMPROW) * DCTSIZE);
    }

    while (p_sys->p_jpeg.next_scanline < p_sys->p_jpeg.image_height)
    {
        for (int i = 0; i < p_pic->i_planes; i++)
        {
            int i_offset = p_sys->p_jpeg.next_scanline * p_sys->p_jpeg.comp_info[i].v_samp_factor / p_sys->p_jpeg.max_v_samp_factor;

            for (int j = 0; j < p_sys->p_jpeg.comp_info[i].v_samp_factor * DCTSIZE; j++)
            {
                p_row_pointers[i][j] = p_pic->p[i].p_pixels + p_pic->p[i].i_pitch * (i_offset + j);
            }
        }
        jpeg_write_raw_data(&p_sys->p_jpeg, p_row_pointers, p_sys->p_jpeg.max_v_samp_factor * DCTSIZE);
    }

    jpeg_finish_compress(&p_sys->p_jpeg);
    jpeg_destroy_compress(&p_sys->p_jpeg);

    for (int i = 0; i < p_pic->i_planes; i++)
    {
        free(p_row_pointers[i]);
    }
    free(p_row_pointers);

    p_block->i_buffer = size;
    p_block->i_dts = p_block->i_pts = p_pic->date;

    return p_block;

error:
    jpeg_destroy_compress(&p_sys->p_jpeg);

    if (p_row_pointers != NULL)
    {
        for (int i = 0; i < p_pic->i_planes; i++)
        {
            free(p_row_pointers[i]);
        }
    }
    free(p_row_pointers);

    block_Release(p_block);

    return NULL;
}