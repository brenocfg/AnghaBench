#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_video_standard; int /*<<< orphan*/  i_video_format_token; TYPE_1__* field_info; int /*<<< orphan*/  i_nb_fields_per_frame; int /*<<< orphan*/  i_frame_height_in_pixels; int /*<<< orphan*/  i_frame_width_in_pixels; int /*<<< orphan*/  i_frame_aspect_ratio; int /*<<< orphan*/  i_v_total_in_lines; int /*<<< orphan*/  i_h_total_in_t; int /*<<< orphan*/  i_vertical_refresh; } ;
typedef  TYPE_2__ avi_chunk_vprp_t ;
typedef  int /*<<< orphan*/  avi_chunk_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_video_y_valid_start_line; int /*<<< orphan*/  i_video_x_offset_in_t; int /*<<< orphan*/  i_valid_bm_y_offset; int /*<<< orphan*/  i_valid_bm_x_offset; int /*<<< orphan*/  i_valid_bm_width; int /*<<< orphan*/  i_valid_bm_height; int /*<<< orphan*/  i_compressed_bm_width; int /*<<< orphan*/  i_compressed_bm_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_READ4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVI_READCHUNK_ENTER ; 
 int /*<<< orphan*/  AVI_READCHUNK_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 unsigned int __MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AVI_ChunkRead_vprp( stream_t *s, avi_chunk_t *p_chk )
{
    avi_chunk_vprp_t *p_vprp = (avi_chunk_vprp_t*)p_chk;

    AVI_READCHUNK_ENTER;

    AVI_READ4BYTES( p_vprp->i_video_format_token );
    AVI_READ4BYTES( p_vprp->i_video_standard );
    AVI_READ4BYTES( p_vprp->i_vertical_refresh );
    AVI_READ4BYTES( p_vprp->i_h_total_in_t );
    AVI_READ4BYTES( p_vprp->i_v_total_in_lines );
    AVI_READ4BYTES( p_vprp->i_frame_aspect_ratio );
    AVI_READ4BYTES( p_vprp->i_frame_width_in_pixels );
    AVI_READ4BYTES( p_vprp->i_frame_height_in_pixels );
    AVI_READ4BYTES( p_vprp->i_nb_fields_per_frame );
    for( unsigned i = 0; i < __MIN( p_vprp->i_nb_fields_per_frame, 2 ); i++ )
    {
        AVI_READ4BYTES( p_vprp->field_info[i].i_compressed_bm_height );
        AVI_READ4BYTES( p_vprp->field_info[i].i_compressed_bm_width );
        AVI_READ4BYTES( p_vprp->field_info[i].i_valid_bm_height );
        AVI_READ4BYTES( p_vprp->field_info[i].i_valid_bm_width );
        AVI_READ4BYTES( p_vprp->field_info[i].i_valid_bm_x_offset );
        AVI_READ4BYTES( p_vprp->field_info[i].i_valid_bm_y_offset );
        AVI_READ4BYTES( p_vprp->field_info[i].i_video_x_offset_in_t );
        AVI_READ4BYTES( p_vprp->field_info[i].i_video_y_valid_start_line );
    }

#ifdef AVI_DEBUG
    msg_Dbg( (vlc_object_t*)s, "vprp: format:%d standard:%d",
             p_vprp->i_video_format_token, p_vprp->i_video_standard );
#endif
    AVI_READCHUNK_EXIT( VLC_SUCCESS );
}