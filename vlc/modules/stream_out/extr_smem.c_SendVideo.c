#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ sout_stream_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* pf_video_postrender_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pf_video_prerender_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t) ;} ;
typedef  TYPE_4__ sout_stream_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_bits_per_pixel; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_12__ {TYPE_1__ video; } ;
struct TYPE_15__ {TYPE_2__ format; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_5__ sout_stream_id_sys_t ;
struct TYPE_16__ {size_t i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SendVideo( sout_stream_t *p_stream, void *_id, block_t *p_buffer )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    size_t i_size = p_buffer->i_buffer;
    uint8_t* p_pixels = NULL;

    /* Calling the prerender callback to get user buffer */
    p_sys->pf_video_prerender_callback( id->p_data, &p_pixels, i_size );

    if (!p_pixels)
    {
        msg_Err( p_stream, "No buffer given!" );
        block_ChainRelease( p_buffer );
        return VLC_EGENERIC;
    }

    /* Copying data into user buffer */
    memcpy( p_pixels, p_buffer->p_buffer, i_size );
    /* Calling the postrender callback to tell the user his buffer is ready */
    p_sys->pf_video_postrender_callback( id->p_data, p_pixels,
                                         id->format.video.i_width, id->format.video.i_height,
                                         id->format.video.i_bits_per_pixel, i_size, p_buffer->i_pts );
    block_ChainRelease( p_buffer );
    return VLC_SUCCESS;
}