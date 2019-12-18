#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vcddev_t ;
struct TYPE_4__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/ * pf_block; int /*<<< orphan*/ * pf_read; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {scalar_t__ i_cdda_tracks; int /*<<< orphan*/ * p_toc; int /*<<< orphan*/ * cddb; int /*<<< orphan*/ * mbrecord; int /*<<< orphan*/  i_cdda_last; int /*<<< orphan*/  i_cdda_first; scalar_t__ cdtextc; int /*<<< orphan*/ * cdtextv; int /*<<< orphan*/ * vcddev; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AccessControl ; 
 int /*<<< orphan*/ * GetCDDBInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetMusicbrainzInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadDir ; 
 scalar_t__ TOC_GetAudioRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  ioctl_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl_GetCdText (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/ * ioctl_GetTOC (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcddev_toc_Free (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int AccessOpen(vlc_object_t *obj, vcddev_t *dev)
{
    stream_t *access = (stream_t *)obj;
    /* Only whole discs here */
    access_sys_t *sys = vlc_obj_malloc(obj, sizeof (*sys));
    if (unlikely(sys == NULL))
    {
        ioctl_Close(obj, dev);
        return VLC_ENOMEM;
    }

    sys->vcddev = dev;
    sys->p_toc = ioctl_GetTOC(obj, dev, true);
    if (sys->p_toc == NULL)
    {
        msg_Err(obj, "cannot count tracks");
        goto error;
    }

    sys->i_cdda_tracks = TOC_GetAudioRange(sys->p_toc, &sys->i_cdda_first, &sys->i_cdda_last);
    if (sys->i_cdda_tracks == 0)
    {
        msg_Err(obj, "no audio tracks found");
        vcddev_toc_Free(sys->p_toc);
        goto error;
    }

    if (ioctl_GetCdText(obj, dev, &sys->cdtextv, &sys->cdtextc))
    {
        msg_Dbg(obj, "CD-TEXT information missing");
        sys->cdtextv = NULL;
        sys->cdtextc = 0;
    }

    sys->mbrecord = NULL;
#ifdef HAVE_LIBCDDB
    sys->cddb = NULL;
#endif

    if(var_InheritBool(obj, "metadata-network-access"))
    {
        sys->mbrecord = GetMusicbrainzInfo(obj, sys->p_toc, sys->i_cdda_tracks,
                                           sys->i_cdda_first, sys->i_cdda_last );
#ifdef HAVE_LIBCDDB
        if(!sys->mbrecord)
            sys->cddb = GetCDDBInfo(obj, sys->p_toc);
#endif
    }
    else msg_Dbg(obj, "album art policy set to manual: not fetching");

    access->p_sys = sys;
    access->pf_read = NULL;
    access->pf_block = NULL;
    access->pf_readdir = ReadDir;
    access->pf_seek = NULL;
    access->pf_control = AccessControl;
    return VLC_SUCCESS;

error:
    ioctl_Close(obj, dev);
    return VLC_EGENERIC;
}