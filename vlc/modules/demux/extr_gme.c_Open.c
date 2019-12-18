#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_23__ {int /*<<< orphan*/  psz_name; int /*<<< orphan*/  i_length; } ;
typedef  TYPE_2__ input_title_t ;
struct TYPE_24__ {int length; scalar_t__* song; } ;
typedef  TYPE_3__ gme_info_t ;
struct TYPE_22__ {int i_rate; int i_bytes_per_frame; int i_frame_length; int i_channels; int i_blockalign; int i_bitspersample; } ;
struct TYPE_25__ {int i_bitrate; TYPE_1__ audio; } ;
typedef  TYPE_4__ es_format_t ;
struct TYPE_26__ {TYPE_6__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  out; TYPE_7__* s; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_27__ {unsigned int titlec; int title_changed; int /*<<< orphan*/ * emu; TYPE_2__** titlev; int /*<<< orphan*/  pts; int /*<<< orphan*/  es; scalar_t__ track_id; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_28__ {scalar_t__ i_buffer; } ;
typedef  TYPE_7__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 scalar_t__ LONG_MAX ; 
 int RATE ; 
 int /*<<< orphan*/  ReaderBlock ; 
 int /*<<< orphan*/  ReaderStream ; 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 int /*<<< orphan*/  gme_free_info (TYPE_3__*) ; 
 int /*<<< orphan*/  gme_identify_extension (char const*) ; 
 char* gme_identify_header (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gme_load_custom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/ * gme_new_emu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gme_start_track (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int gme_track_count (int /*<<< orphan*/ *) ; 
 scalar_t__ gme_track_info (int /*<<< orphan*/ *,TYPE_3__**,unsigned int) ; 
 TYPE_6__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  strdup (scalar_t__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_2__** vlc_alloc (unsigned int,int) ; 
 TYPE_2__* vlc_input_title_New () ; 
 TYPE_7__* vlc_stream_Block (TYPE_7__*,int) ; 
 scalar_t__ vlc_stream_GetSize (TYPE_7__*,scalar_t__*) ; 
 int vlc_stream_Peek (TYPE_7__*,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    uint64_t size;

    if (vlc_stream_GetSize(demux->s, &size))
        return VLC_EGENERIC;
    if (size > LONG_MAX /* too big for GME */)
        return VLC_EGENERIC;

    /* Auto detection */
    const uint8_t *peek;
    if (vlc_stream_Peek (demux->s, &peek, 4) < 4)
        return VLC_EGENERIC;

    const char *type = gme_identify_header (peek);
    if (!*type)
        return VLC_EGENERIC;
    msg_Dbg (obj, "detected file type %s", type);

    block_t *data = NULL;
    if (size <= 0)
    {
        data = vlc_stream_Block (demux->s, 1 << 24);
        if (data == NULL)
            return VLC_EGENERIC;
    }

    /* Initialization */
    demux_sys_t *sys = malloc (sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    sys->emu = gme_new_emu (gme_identify_extension (type), RATE);
    if (sys->emu == NULL)
    {
        free (sys);
        return VLC_ENOMEM;
    }
    if (data)
    {
        gme_load_custom (sys->emu, ReaderBlock, data->i_buffer, data);
        block_Release(data);
    }
    else
    {
        gme_load_custom (sys->emu, ReaderStream, size, demux->s);
    }
    gme_start_track (sys->emu, sys->track_id = 0);

    es_format_t fmt;
    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_S16N);
    fmt.audio.i_rate = RATE;
    fmt.audio.i_bytes_per_frame = 4;
    fmt.audio.i_frame_length = 4;
    fmt.audio.i_channels = 2;
    fmt.audio.i_blockalign = 4;
    fmt.audio.i_bitspersample = 16;
    fmt.i_bitrate = RATE * 4;

    sys->es = es_out_Add (demux->out, &fmt);
    date_Init (&sys->pts, RATE, 1);
    date_Set(&sys->pts, VLC_TICK_0);

    /* Titles */
    unsigned n = gme_track_count (sys->emu);
    sys->titlev = vlc_alloc (n, sizeof (*sys->titlev));
    if (unlikely(sys->titlev == NULL))
        n = 0;
    sys->titlec = n;
    for (unsigned i = 0; i < n; i++)
    {
         input_title_t *title = vlc_input_title_New ();
         sys->titlev[i] = title;
         if (unlikely(title == NULL))
             continue;

         gme_info_t *infos;
         if (gme_track_info (sys->emu, &infos, i))
             continue;
         msg_Dbg (obj, "track %u: %s %d ms", i, infos->song, infos->length);
         if (infos->length != -1)
             title->i_length = VLC_TICK_FROM_MS(infos->length);
         if (infos->song[0])
             title->psz_name = strdup (infos->song);
         gme_free_info (infos);
    }
    sys->title_changed = false;

    /* Callbacks */
    demux->pf_demux = Demux;
    demux->pf_control = Control;
    demux->p_sys = sys;
    return VLC_SUCCESS;
}