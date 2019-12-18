#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_config ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int i_extra_picture_buffers; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
struct TYPE_9__ {int b_add_metavideo; TYPE_3__* p_dec; int /*<<< orphan*/  align; TYPE_2__ info; int /*<<< orphan*/  p_caps; void* b_need_aligned; scalar_t__ p_allocator; } ;
typedef  TYPE_1__ GstVlcVideoPool ;
typedef  TYPE_2__ GstVideoInfo ;
typedef  int /*<<< orphan*/  GstVideoAlignment ;
typedef  int /*<<< orphan*/  GstStructure ;
typedef  int /*<<< orphan*/  GstCaps ;
typedef  int /*<<< orphan*/  GstBufferPool ;
typedef  int /*<<< orphan*/  GstAllocator ;
typedef  int /*<<< orphan*/  GstAllocationParams ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_8__* GST_BUFFER_POOL_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GST_BUFFER_POOL_OPTION_VIDEO_ALIGNMENT ; 
 int /*<<< orphan*/  GST_BUFFER_POOL_OPTION_VIDEO_META ; 
 int /*<<< orphan*/  GST_IS_VLC_PICTURE_PLANE_ALLOCATOR (int /*<<< orphan*/ *) ; 
 TYPE_1__* GST_VLC_VIDEO_POOL_CAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_buffer_pool_config_get_allocator (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_buffer_pool_config_get_params (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_buffer_pool_config_get_video_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* gst_buffer_pool_config_has_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_buffer_pool_config_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_buffer_pool_config_set_video_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_caps_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_caps_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_caps_unref (int /*<<< orphan*/ ) ; 
 scalar_t__ gst_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_object_unref (scalar_t__) ; 
 int /*<<< orphan*/  gst_video_alignment_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_video_info_from_caps (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_query_format (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  parent_class ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean gst_vlc_video_pool_set_config( GstBufferPool *p_pool,
        GstStructure *p_config )
{
    GstVlcVideoPool *p_vpool = GST_VLC_VIDEO_POOL_CAST( p_pool );
    GstCaps *p_caps;
    GstVideoInfo info;
    GstVideoAlignment align;
    guint size, min_buffers, max_buffers;
    GstAllocator *p_allocator;
    GstAllocationParams params;

    if( !gst_buffer_pool_config_get_params( p_config, &p_caps, &size,
                &min_buffers, &max_buffers ))
        goto wrong_config;
    if( p_caps == NULL )
        goto no_caps;

    gst_buffer_pool_config_get_allocator( p_config, &p_allocator, &params );
    if( p_allocator )
    {
        if( !GST_IS_VLC_PICTURE_PLANE_ALLOCATOR( p_allocator ))
            goto unsupported_allocator;
        else
        {
            if( p_vpool->p_allocator )
                gst_object_unref( p_vpool->p_allocator );
            p_vpool->p_allocator = gst_object_ref ( p_allocator );
        }
    }

    /* now parse the caps from the config */
    if ( !gst_video_info_from_caps( &info, p_caps ))
        goto wrong_caps;

    /* enable metadata based on config of the pool */
    p_vpool->b_add_metavideo =
        gst_buffer_pool_config_has_option( p_config,
                GST_BUFFER_POOL_OPTION_VIDEO_META );

    p_vpool->b_need_aligned =
        gst_buffer_pool_config_has_option( p_config,
                GST_BUFFER_POOL_OPTION_VIDEO_ALIGNMENT );

    if( p_vpool->b_need_aligned )
    {
        p_vpool->b_add_metavideo = true;
        gst_buffer_pool_config_get_video_alignment( p_config, &align );
    }
    else
         gst_video_alignment_reset( &align );

    // FIXME: the gst decoders' min buffers may not be equal to the number
    // of buffers it actually allocates. Also the max buffers here could
    // be zero. Moreover even if it was right, need to check if it can be
    // communicated to the vout (including the dpb_size it calculates in
    // src/input/decoder.c).
    p_vpool->p_dec->i_extra_picture_buffers = 16;

    if( !gst_vlc_picture_plane_allocator_query_format( p_vpool->p_allocator,
                &info, &align, p_caps))
        goto unknown_format;

    if( p_vpool->b_need_aligned )
        gst_buffer_pool_config_set_video_alignment( p_config, &align);

    if( p_vpool->p_caps )
        gst_caps_unref( p_vpool->p_caps );
    p_vpool->p_caps = gst_caps_ref( p_caps );
    p_vpool->info = info;
    p_vpool->align = align;

    msg_Dbg( p_vpool->p_dec, "setting the following config on the pool: %s, \
            size: %lu, min buffers: %u, max buffers: %u", gst_caps_to_string( p_caps ),
            info.size, min_buffers, max_buffers );

    gst_buffer_pool_config_set_params( p_config, p_caps, info.size,
            min_buffers, max_buffers );

    return GST_BUFFER_POOL_CLASS (parent_class)->set_config( p_pool, p_config );

    /* ERRORS */
wrong_config:
    {
        msg_Err(p_vpool->p_dec, "wrong pool config" );
        return FALSE;
    }
no_caps:
    {
        msg_Err(p_vpool->p_dec, "no input caps in config" );
        return FALSE;
    }
wrong_caps:
    {
        msg_Err(p_vpool->p_dec, "invalid caps" );
        return FALSE;
    }
unknown_format:
    {
        msg_Err(p_vpool->p_dec, "format unsupported" );
        return FALSE;
    }
unsupported_allocator:
    {
        msg_Err(p_vpool->p_dec, "allocator unsupported" );
        return FALSE;
    }
}