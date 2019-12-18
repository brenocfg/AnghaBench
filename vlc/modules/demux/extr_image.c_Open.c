#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_19__ {int i_frame_rate; int i_frame_rate_base; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_20__ {TYPE_1__ video; void* i_group; void* i_id; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_21__ {TYPE_4__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  out; int /*<<< orphan*/  s; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_22__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  pts_next; scalar_t__ is_realtime; int /*<<< orphan*/  pts_offset; int /*<<< orphan*/  duration; int /*<<< orphan*/  es; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ demux_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/ * Decode (TYPE_3__*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Demux ; 
 scalar_t__ Detect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Load (TYPE_3__*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 scalar_t__ VLC_CODEC_MXPEG ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_2__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 scalar_t__ var_InheritBool (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  var_InheritFloat (TYPE_3__*,char*) ; 
 void* var_InheritInteger (TYPE_3__*,char*) ; 
 char* var_InheritString (TYPE_3__*,char*) ; 
 scalar_t__ var_InheritURational (TYPE_3__*,int*,int*,char*) ; 
 scalar_t__ vlc_fourcc_GetCodecFromString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_fourcc_GetDescription (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vlc_tick_from_sec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static int Open(vlc_object_t *object)
{
    demux_t *demux = (demux_t*)object;

    /* Detect the image type */
    vlc_fourcc_t codec = Detect(demux->s);
    if (codec == 0)
        return VLC_EGENERIC;

    msg_Dbg(demux, "Detected image: %s",
            vlc_fourcc_GetDescription(VIDEO_ES, codec));

    if (codec == VLC_CODEC_MXPEG)
        return VLC_EGENERIC; //let avformat demux this file

    /* Load and if selected decode */
    es_format_t fmt;
    es_format_Init(&fmt, VIDEO_ES, codec);
    fmt.video.i_chroma = fmt.i_codec;

    block_t *data = Load(demux);
    if (data && var_InheritBool(demux, "image-decode")) {
        char *string = var_InheritString(demux, "image-chroma");
        vlc_fourcc_t chroma = vlc_fourcc_GetCodecFromString(VIDEO_ES, string);
        free(string);

        data = Decode(demux, &fmt, chroma, data);
    }
    fmt.i_id    = var_InheritInteger(demux, "image-id");
    fmt.i_group = var_InheritInteger(demux, "image-group");
    if (var_InheritURational(demux,
                             &fmt.video.i_frame_rate,
                             &fmt.video.i_frame_rate_base,
                             "image-fps") ||
        fmt.video.i_frame_rate <= 0 || fmt.video.i_frame_rate_base <= 0) {
        msg_Err(demux, "Invalid frame rate, using 10/1 instead");
        fmt.video.i_frame_rate      = 10;
        fmt.video.i_frame_rate_base = 1;
    }

    /* If loadind failed, we still continue to avoid mis-detection
     * by other demuxers. */
    if (!data)
        msg_Err(demux, "Failed to load the image");

    /* */
    demux_sys_t *sys = malloc(sizeof(*sys));
    if (!sys) {
        if (data)
            block_Release(data);
        es_format_Clean(&fmt);
        return VLC_ENOMEM;
    }

    sys->data        = data;
    sys->es          = es_out_Add(demux->out, &fmt);
    sys->duration    = vlc_tick_from_sec( var_InheritFloat(demux, "image-duration") );
    sys->is_realtime = var_InheritBool(demux, "image-realtime");
    sys->pts_offset  = sys->is_realtime ? vlc_tick_now() : 0;
    sys->pts_next    = VLC_TICK_INVALID;
    date_Init(&sys->pts, fmt.video.i_frame_rate, fmt.video.i_frame_rate_base);
    date_Set(&sys->pts, VLC_TICK_0);

    es_format_Clean(&fmt);

    demux->pf_demux   = Demux;
    demux->pf_control = Control;
    demux->p_sys      = sys;
    return VLC_SUCCESS;
}