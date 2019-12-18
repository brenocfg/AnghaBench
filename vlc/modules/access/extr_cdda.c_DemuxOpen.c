#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_15__ {int i_last_track; TYPE_1__* p_sectors; } ;
typedef  TYPE_3__ vcddev_toc_t ;
typedef  int /*<<< orphan*/  vcddev_t ;
struct TYPE_14__ {int i_rate; int i_channels; } ;
struct TYPE_16__ {TYPE_2__ audio; } ;
typedef  TYPE_4__ es_format_t ;
struct TYPE_17__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/ * out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_18__ {void* start; unsigned int length; scalar_t__ position; int /*<<< orphan*/  pts; int /*<<< orphan*/  es; int /*<<< orphan*/ * vcddev; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_13__ {int i_lba; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 scalar_t__ CD_ROM_XA_INTERVAL ; 
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  DemuxControl ; 
 int TOC_GetAudioRange (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  VLC_CODEC_S16L ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ioctl_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* ioctl_GetTOC (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 void* var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcddev_toc_Free (TYPE_3__*) ; 
 TYPE_6__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int DemuxOpen(vlc_object_t *obj, vcddev_t *dev, unsigned track)
{
    demux_t *demux = (demux_t *)obj;

    if (demux->out == NULL)
        goto error;

    demux_sys_t *sys = vlc_obj_malloc(obj, sizeof (*sys));
    if (unlikely(sys == NULL))
        goto error;

    demux->p_sys = sys;
    sys->vcddev = dev;
    sys->start = var_InheritInteger(obj, "cdda-first-sector");
    sys->length = var_InheritInteger(obj, "cdda-last-sector") - sys->start;

    /* Track number in input item */
    if (sys->start == (unsigned)-1 || sys->length == (unsigned)-1)
    {
        vcddev_toc_t *p_toc = ioctl_GetTOC(obj, dev, true);
        if(p_toc == NULL)
            goto error;

        int i_cdda_tracks, i_cdda_first, i_cdda_last;
        i_cdda_tracks = TOC_GetAudioRange(p_toc, &i_cdda_first, &i_cdda_last);

        if (track == 0 || track > (unsigned) i_cdda_tracks)
        {
            msg_Err(obj, "invalid track number: %u/%i", track, i_cdda_tracks);
            vcddev_toc_Free(p_toc);
            goto error;
        }

        track--;
        int i_first_sector = p_toc->p_sectors[track].i_lba;
        int i_last_sector = p_toc->p_sectors[track + 1].i_lba;
        if(i_cdda_first + track == (unsigned) i_cdda_last && p_toc->i_last_track > i_cdda_last)
            i_last_sector -= CD_ROM_XA_INTERVAL;

        sys->start = i_first_sector;
        sys->length = i_last_sector - i_first_sector;
        vcddev_toc_Free(p_toc);
    }

    es_format_t fmt;

    es_format_Init(&fmt, AUDIO_ES, VLC_CODEC_S16L);
    fmt.audio.i_rate = 44100;
    fmt.audio.i_channels = 2;
    sys->es = es_out_Add(demux->out, &fmt);

    date_Init(&sys->pts, 44100, 1);
    date_Set(&sys->pts, VLC_TICK_0);

    sys->position = 0;
    demux->pf_demux = Demux;
    demux->pf_control = DemuxControl;
    return VLC_SUCCESS;

error:
    ioctl_Close(obj, dev);
    return VLC_EGENERIC;
}