#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__ p_dec; int /*<<< orphan*/  (* new_caps ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  vinfo; } ;
typedef  TYPE_1__ GstVlcVideoSink ;
typedef  int /*<<< orphan*/  GstVideoInfo ;
typedef  int /*<<< orphan*/  GstCaps ;
typedef  int /*<<< orphan*/  GstBaseSink ;
typedef  TYPE_2__ GValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GST_ELEMENT_CAST (TYPE_1__*) ; 
 int /*<<< orphan*/  GST_TYPE_CAPS ; 
 int /*<<< orphan*/  GST_TYPE_ELEMENT ; 
 TYPE_1__* GST_VLC_VIDEO_SINK (int /*<<< orphan*/ *) ; 
 size_t SIGNAL_NEW_CAPS ; 
 int /*<<< orphan*/  g_signal_emitv (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_value_set_boxed (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_value_set_object (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gst_video_info_from_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gst_vlc_video_sink_signals ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean gst_vlc_video_sink_setcaps( GstBaseSink *p_basesink,
        GstCaps *p_caps )
{
    GstVlcVideoSink *p_vsink = GST_VLC_VIDEO_SINK( p_basesink );
    GstVideoInfo info;
    gboolean b_ret = FALSE;

   //FIXME caps_signal
#if 0
    GValue ret = { 0 };
    GValue args[2] = { {0}, {0} };
#endif

    if( !gst_video_info_from_caps( &info, p_caps ))
        return FALSE;

    p_vsink->vinfo = info;

    //FIXME caps_signal
#if 0
    g_value_init( &args[0], GST_TYPE_ELEMENT );
    g_value_set_object( &args[0], p_vsink );
    g_value_init( &args[1], GST_TYPE_CAPS );
    g_value_set_boxed( &args[1], p_caps );

    g_signal_emitv( args, gst_vlc_video_sink_signals[ SIGNAL_NEW_CAPS ],
            0, &b_ret );
#else
    b_ret = p_vsink->new_caps( GST_ELEMENT_CAST( p_vsink ), p_caps,
            (gpointer) p_vsink->p_dec );
#endif

    return b_ret;
}