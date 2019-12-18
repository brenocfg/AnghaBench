#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int i_entries; int /*<<< orphan*/ ** palette; } ;
typedef  TYPE_1__ video_palette_t ;
struct TYPE_22__ {int i_sar_num; int i_sar_den; TYPE_1__* p_palette; scalar_t__ i_y_offset; scalar_t__ i_x_offset; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_2__ video_format_t ;
struct TYPE_23__ {int b_ephemer; TYPE_4__* p_region; scalar_t__ i_stop; scalar_t__ i_start; } ;
typedef  TYPE_3__ subpicture_t ;
struct TYPE_24__ {int i_x; int /*<<< orphan*/  i_y; } ;
typedef  TYPE_4__ subpicture_region_t ;
struct TYPE_25__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_26__ {int i_x_start; int /*<<< orphan*/  i_y_start; int /*<<< orphan*/ ** p_palette; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; scalar_t__ i_duration; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_27__ {scalar_t__ i_pts; } ;
typedef  TYPE_7__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  RenderImage (TYPE_5__*,TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  VLC_CODEC_YUVP ; 
 TYPE_3__* decoder_NewSubpicture (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  subpicture_Delete (TYPE_3__*) ; 
 TYPE_4__* subpicture_region_New (TYPE_2__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static subpicture_t *DecodePacket( decoder_t *p_dec, block_t *p_data )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    subpicture_t  *p_spu;
    subpicture_region_t *p_region;
    video_format_t fmt;
    video_palette_t palette;
    int i;

    /* Allocate the subpicture internal data. */
    p_spu = decoder_NewSubpicture( p_dec, NULL );
    if( !p_spu ) return NULL;

    p_spu->i_start = p_data->i_pts;
    p_spu->i_stop  = p_data->i_pts + p_sys->i_duration;
    p_spu->b_ephemer = true;

    /* Create new SPU region */
    video_format_Init( &fmt, VLC_CODEC_YUVP );
    fmt.i_sar_num = 1;
    fmt.i_sar_den = 1;
    fmt.i_width = fmt.i_visible_width = p_sys->i_width;
    fmt.i_height = fmt.i_visible_height = p_sys->i_height;
    fmt.i_x_offset = fmt.i_y_offset = 0;
    fmt.p_palette = &palette;
    fmt.p_palette->i_entries = 4;
    for( i = 0; i < fmt.p_palette->i_entries; i++ )
    {
        fmt.p_palette->palette[i][0] = p_sys->p_palette[i][0];
        fmt.p_palette->palette[i][1] = p_sys->p_palette[i][1];
        fmt.p_palette->palette[i][2] = p_sys->p_palette[i][2];
        fmt.p_palette->palette[i][3] = p_sys->p_palette[i][3];
    }

    p_region = subpicture_region_New( &fmt );
    if( !p_region )
    {
        msg_Err( p_dec, "cannot allocate SPU region" );
        subpicture_Delete( p_spu );
        return NULL;
    }

    p_spu->p_region = p_region;
    p_region->i_x = p_sys->i_x_start;
    p_region->i_x = p_region->i_x * 3 / 4; /* FIXME: use aspect ratio for x? */
    p_region->i_y = p_sys->i_y_start;

    RenderImage( p_dec, p_data, p_region );

    return p_spu;
}