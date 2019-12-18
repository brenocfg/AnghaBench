#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GstBufferPool ;

/* Variables and functions */
#define  GST_BUFFER_POOL_OPTION_VIDEO_ALIGNMENT 129 
#define  GST_BUFFER_POOL_OPTION_VIDEO_META 128 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const gchar** gst_vlc_video_pool_get_options (GstBufferPool *p_pool)
{
    VLC_UNUSED( p_pool );

    static const gchar *options[] = { GST_BUFFER_POOL_OPTION_VIDEO_META,
        GST_BUFFER_POOL_OPTION_VIDEO_ALIGNMENT, NULL
    };

    return options;
}