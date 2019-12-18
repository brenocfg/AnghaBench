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
struct TYPE_4__ {int /*<<< orphan*/  finalize; } ;
struct TYPE_3__ {int /*<<< orphan*/  release_buffer; int /*<<< orphan*/  acquire_buffer; int /*<<< orphan*/  free_buffer; int /*<<< orphan*/  alloc_buffer; int /*<<< orphan*/  set_config; int /*<<< orphan*/  get_options; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  GstVlcVideoPoolClass ;
typedef  TYPE_1__ GstBufferPoolClass ;
typedef  TYPE_2__ GObjectClass ;

/* Variables and functions */
 int /*<<< orphan*/  gst_vlc_video_pool_acquire_buffer ; 
 int /*<<< orphan*/  gst_vlc_video_pool_alloc_buffer ; 
 int /*<<< orphan*/  gst_vlc_video_pool_finalize ; 
 int /*<<< orphan*/  gst_vlc_video_pool_free_buffer ; 
 int /*<<< orphan*/  gst_vlc_video_pool_get_options ; 
 int /*<<< orphan*/  gst_vlc_video_pool_release_buffer ; 
 int /*<<< orphan*/  gst_vlc_video_pool_set_config ; 
 int /*<<< orphan*/  gst_vlc_video_pool_start ; 

__attribute__((used)) static void gst_vlc_video_pool_class_init( GstVlcVideoPoolClass *p_klass )
{
    GObjectClass *p_gobject_class = ( GObjectClass* )p_klass;
    GstBufferPoolClass *p_gstbufferpool_class = ( GstBufferPoolClass* )p_klass;

    p_gobject_class->finalize = gst_vlc_video_pool_finalize;

    p_gstbufferpool_class->start = gst_vlc_video_pool_start;
    p_gstbufferpool_class->get_options = gst_vlc_video_pool_get_options;
    p_gstbufferpool_class->set_config = gst_vlc_video_pool_set_config;
    p_gstbufferpool_class->alloc_buffer = gst_vlc_video_pool_alloc_buffer;
    p_gstbufferpool_class->free_buffer = gst_vlc_video_pool_free_buffer;
    p_gstbufferpool_class->acquire_buffer = gst_vlc_video_pool_acquire_buffer;
    p_gstbufferpool_class->release_buffer = gst_vlc_video_pool_release_buffer;
}