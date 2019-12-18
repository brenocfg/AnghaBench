#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_38__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_43__ {int /*<<< orphan*/ * p_srccaps; int /*<<< orphan*/ * p_sinkcaps; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ sink_src_caps_t ;
typedef  int /*<<< orphan*/  guint64 ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  TYPE_2__* gboolean ;
struct TYPE_46__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_4__* p_sys; int /*<<< orphan*/  fmt_in; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_47__ {int b_prerolled; int b_running; TYPE_2__* p_decoder; TYPE_2__* p_decode_out; TYPE_2__* p_decode_in; TYPE_2__* p_decode_src; TYPE_2__* p_bus; int /*<<< orphan*/  p_allocator; TYPE_2__* p_que; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_48__ {int /*<<< orphan*/  seek_data; int /*<<< orphan*/ * need_data; int /*<<< orphan*/ * enough_data; } ;
struct TYPE_45__ {int /*<<< orphan*/  new_caps; } ;
struct TYPE_44__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  GstStructure ;
typedef  TYPE_2__* GstStateChangeReturn ;
typedef  int /*<<< orphan*/  GstElementFactory ;
typedef  TYPE_6__ GstAppSrcCallbacks ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  CloseDecoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DecodeBlock ; 
 int /*<<< orphan*/ * FALSE ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  GST_APP_SRC (TYPE_2__*) ; 
 int /*<<< orphan*/  GST_APP_STREAM_TYPE_SEEKABLE ; 
 int /*<<< orphan*/  GST_BIN (TYPE_2__*) ; 
 TYPE_2__* GST_ELEMENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GST_ELEMENT_FACTORY_TYPE_DECODER ; 
 int /*<<< orphan*/  GST_FORMAT_BYTES ; 
 int /*<<< orphan*/  GST_RANK_MARGINAL ; 
 int /*<<< orphan*/ * GST_STATE_CHANGE_FAILURE ; 
 int /*<<< orphan*/  GST_STATE_PLAYING ; 
 TYPE_38__* GST_VLC_VIDEO_SINK (TYPE_2__*) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_ENOMOD ; 
 int /*<<< orphan*/  VLC_GST_CHECK (TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int VLC_SUCCESS ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  caps_handoff_cb ; 
 int /*<<< orphan*/  find_decoder_func ; 
 int /*<<< orphan*/  frame_handoff_cb ; 
 TYPE_2__* g_list_find_custom (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_list_sort (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int,char*,...) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  gst_app_src_set_callbacks (int /*<<< orphan*/ ,TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* gst_atomic_queue_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_bin_add_many (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_bin_new (char*) ; 
 TYPE_2__* gst_bus_new () ; 
 int /*<<< orphan*/  gst_caps_append_structure (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gst_caps_new_empty () ; 
 int /*<<< orphan*/ * gst_caps_new_empty_simple (char*) ; 
 int /*<<< orphan*/  gst_caps_unref (int /*<<< orphan*/ *) ; 
 TYPE_2__* gst_element_factory_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* gst_element_factory_list_get_elements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gst_element_factory_make (char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* gst_element_link (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gst_element_set_bus (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* gst_element_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_object_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  gst_plugin_feature_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  gst_plugin_feature_rank_compare_func ; 
 int /*<<< orphan*/  gst_structure_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_vlc_picture_plane_allocator_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pad_added_cb ; 
 int /*<<< orphan*/  seek_data_cb ; 
 int var_CreateGetBool (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_gst_init () ; 
 int /*<<< orphan*/ * vlc_to_gst_fmt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int OpenDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = ( decoder_t* )p_this;
    decoder_sys_t *p_sys;
    GstStateChangeReturn i_ret;
    gboolean b_ret;
    sink_src_caps_t caps = { NULL, NULL };
    GstStructure *p_str;
    GstAppSrcCallbacks cb;
    int i_rval = VLC_SUCCESS;
    GList *p_list;
    bool dbin, vlc_pool;

#define VLC_GST_CHECK( r, v, s, t ) \
    { if( r == v ){ msg_Err( p_dec, s ); i_rval = t; goto fail; } }

    if( !vlc_gst_init( ))
    {
        msg_Err( p_dec, "failed to register vlcvideosink" );
        return VLC_EGENERIC;
    }

    p_str = vlc_to_gst_fmt( &p_dec->fmt_in );
    if( !p_str )
        return VLC_EGENERIC;

    /* Allocate the memory needed to store the decoder's structure */
    p_sys = p_dec->p_sys = calloc( 1, sizeof( *p_sys ) );
    if( p_sys == NULL )
    {
        gst_structure_free( p_str );
        return VLC_ENOMEM;
    }

    dbin = var_CreateGetBool( p_dec, "use-decodebin" );
    msg_Dbg( p_dec, "Using decodebin? %s", dbin ? "yes ":"no" );

    caps.p_sinkcaps = gst_caps_new_empty( );
    gst_caps_append_structure( caps.p_sinkcaps, p_str );
    /* Currently supports only system memory raw output format */
    caps.p_srccaps = gst_caps_new_empty_simple( "video/x-raw" );

    /* Get the list of all the available gstreamer decoders */
    p_list = gst_element_factory_list_get_elements(
            GST_ELEMENT_FACTORY_TYPE_DECODER, GST_RANK_MARGINAL );
    VLC_GST_CHECK( p_list, NULL, "no decoder list found", VLC_ENOMOD );
    if( !dbin )
    {
        GList *p_l;
        /* Sort them as per ranks */
        p_list = g_list_sort( p_list, gst_plugin_feature_rank_compare_func );
        VLC_GST_CHECK( p_list, NULL, "failed to sort decoders list",
                VLC_ENOMOD );
        p_l = g_list_find_custom( p_list, &caps, find_decoder_func );
        VLC_GST_CHECK( p_l, NULL, "no suitable decoder found",
                VLC_ENOMOD );
        /* create the decoder with highest rank */
        p_sys->p_decode_in = gst_element_factory_create(
                ( GstElementFactory* )p_l->data, NULL );
        VLC_GST_CHECK( p_sys->p_decode_in, NULL,
                "failed to create decoder", VLC_ENOMOD );
    }
    else
    {
        GList *p_l;
        /* Just check if any suitable decoder exists, rest will be
         * handled by decodebin */
        p_l = g_list_find_custom( p_list, &caps, find_decoder_func );
        VLC_GST_CHECK( p_l, NULL, "no suitable decoder found",
                VLC_ENOMOD );
    }
    gst_plugin_feature_list_free( p_list );
    p_list = NULL;
    gst_caps_unref( caps.p_srccaps );
    caps.p_srccaps = NULL;

    p_sys->b_prerolled = false;
    p_sys->b_running = false;

    /* Queue: GStreamer thread will dump buffers into this queue,
     * DecodeBlock() will pop out the buffers from the queue */
    p_sys->p_que = gst_atomic_queue_new( 0 );
    VLC_GST_CHECK( p_sys->p_que, NULL, "failed to create queue",
            VLC_ENOMEM );

    p_sys->p_decode_src = gst_element_factory_make( "appsrc", NULL );
    VLC_GST_CHECK( p_sys->p_decode_src, NULL, "appsrc not found",
            VLC_ENOMOD );
    g_object_set( G_OBJECT( p_sys->p_decode_src ), "caps", caps.p_sinkcaps,
            "emit-signals", TRUE, "format", GST_FORMAT_BYTES,
            "stream-type", GST_APP_STREAM_TYPE_SEEKABLE,
            /* Making DecodeBlock() to block on appsrc with max queue size of 1 byte.
             * This will make the push_buffer() tightly coupled with the buffer
             * flow from appsrc -> decoder. push_buffer() will only return when
             * the same buffer it just fed to appsrc has also been fed to the
             * decoder element as well */
            "block", TRUE, "max-bytes", ( guint64 )1, NULL );
    gst_caps_unref( caps.p_sinkcaps );
    caps.p_sinkcaps = NULL;
    cb.enough_data = NULL;
    cb.need_data = NULL;
    cb.seek_data = seek_data_cb;
    gst_app_src_set_callbacks( GST_APP_SRC( p_sys->p_decode_src ),
            &cb, p_dec, NULL );

    if( dbin )
    {
        p_sys->p_decode_in = gst_element_factory_make( "decodebin", NULL );
        VLC_GST_CHECK( p_sys->p_decode_in, NULL, "decodebin not found",
                VLC_ENOMOD );
        //g_object_set( G_OBJECT( p_sys->p_decode_in ),
        //"max-size-buffers", 2, NULL );
        //g_signal_connect( G_OBJECT( p_sys->p_decode_in ), "no-more-pads",
                //G_CALLBACK( no_more_pads_cb ), p_dec );
        g_signal_connect( G_OBJECT( p_sys->p_decode_in ), "pad-added",
                G_CALLBACK( pad_added_cb ), p_dec );

    }

    /* videosink: will emit signal for every available buffer */
    p_sys->p_decode_out = gst_element_factory_make( "vlcvideosink", NULL );
    VLC_GST_CHECK( p_sys->p_decode_out, NULL, "vlcvideosink not found",
            VLC_ENOMOD );

    vlc_pool = var_CreateGetBool( p_dec, "use-vlcpool" );
    msg_Dbg( p_dec, "Using vlc pool? %s", vlc_pool ? "yes ":"no" );

    p_sys->p_allocator = gst_vlc_picture_plane_allocator_new(
            (gpointer) p_dec );
    g_object_set( G_OBJECT( p_sys->p_decode_out ), "sync", FALSE, "allocator",
            p_sys->p_allocator, "id", (gpointer) p_dec, "use-pool", vlc_pool, NULL );
    g_signal_connect( G_OBJECT( p_sys->p_decode_out ), "new-buffer",
            G_CALLBACK( frame_handoff_cb ), p_dec );

    //FIXME: caps_signal
#if 0
    g_signal_connect( G_OBJECT( p_sys->p_decode_out ), "new-caps",
            G_CALLBACK( caps_handoff_cb ), p_dec );
#else
    GST_VLC_VIDEO_SINK( p_sys->p_decode_out )->new_caps = caps_handoff_cb;
#endif

    p_sys->p_decoder = GST_ELEMENT( gst_bin_new( "decoder" ) );
    VLC_GST_CHECK( p_sys->p_decoder, NULL, "bin not found", VLC_ENOMOD );
    p_sys->p_bus = gst_bus_new( );
    VLC_GST_CHECK( p_sys->p_bus, NULL, "failed to create bus",
            VLC_ENOMOD );
    gst_element_set_bus( p_sys->p_decoder, p_sys->p_bus );

    gst_bin_add_many( GST_BIN( p_sys->p_decoder ),
            p_sys->p_decode_src, p_sys->p_decode_in,
            p_sys->p_decode_out, NULL );
    gst_object_ref( p_sys->p_decode_src );
    gst_object_ref( p_sys->p_decode_in );
    gst_object_ref( p_sys->p_decode_out );

    b_ret = gst_element_link( p_sys->p_decode_src, p_sys->p_decode_in );
    VLC_GST_CHECK( b_ret, FALSE, "failed to link src <-> in",
            VLC_EGENERIC );

    if( !dbin )
    {
        b_ret = gst_element_link( p_sys->p_decode_in, p_sys->p_decode_out );
        VLC_GST_CHECK( b_ret, FALSE, "failed to link in <-> out",
                VLC_EGENERIC );
    }

    /* set the pipeline to playing */
    i_ret = gst_element_set_state( p_sys->p_decoder, GST_STATE_PLAYING );
    VLC_GST_CHECK( i_ret, GST_STATE_CHANGE_FAILURE,
            "set state failure", VLC_EGENERIC );
    p_sys->b_running = true;

    /* Set callbacks */
    p_dec->pf_decode = DecodeBlock;
    p_dec->pf_flush  = Flush;

    return VLC_SUCCESS;

fail:
    if( caps.p_sinkcaps )
        gst_caps_unref( caps.p_sinkcaps );
    if( caps.p_srccaps )
        gst_caps_unref( caps.p_srccaps );
    if( p_list )
        gst_plugin_feature_list_free( p_list );
    CloseDecoder( ( vlc_object_t* )p_dec );
    return i_rval;
}