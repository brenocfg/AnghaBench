#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int uint8_t ;
struct TYPE_17__ {scalar_t__ i_height; int i_width; scalar_t__ orientation; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_14__ {TYPE_5__ video; } ;
struct TYPE_12__ {scalar_t__ i_height; int i_width; scalar_t__ orientation; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_13__ {TYPE_10__ video; } ;
struct TYPE_15__ {TYPE_2__ fmt_out; TYPE_1__ fmt_in; TYPE_4__* p_sys; int /*<<< orphan*/  pf_video_filter; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_16__ {int derive_failed; int image_fallback_failed; int /*<<< orphan*/ * dec_device; int /*<<< orphan*/ * dest_pics; int /*<<< orphan*/  cache; int /*<<< orphan*/ * dpy; int /*<<< orphan*/  va_surface_ids; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 scalar_t__ CheckFmt (TYPE_10__*,TYPE_5__*,int*,int*) ; 
 scalar_t__ CopyInitCache (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DEST_PICS_POOL_SZ ; 
 int /*<<< orphan*/  DownloadSurface ; 
 int /*<<< orphan*/  UploadSurface ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int,scalar_t__,char const*,char const*) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_vaapi_FilterHoldInstance (TYPE_3__* const,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vlc_vaapi_FilterReleaseInstance (TYPE_3__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_vaapi_PoolNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int) ; 

int
vlc_vaapi_OpenChroma(vlc_object_t *obj)
{
    filter_t *const     filter = (filter_t *)obj;
    filter_sys_t *      filter_sys;

    if (filter->fmt_in.video.i_height != filter->fmt_out.video.i_height
     || filter->fmt_in.video.i_width != filter->fmt_out.video.i_width
     || filter->fmt_in.video.orientation != filter->fmt_out.video.orientation)
        return VLC_EGENERIC;

    bool is_upload;
    uint8_t pixel_bytes;
    if (CheckFmt(&filter->fmt_in.video, &filter->fmt_out.video, &is_upload,
                 &pixel_bytes))
        return VLC_EGENERIC;

    filter->pf_video_filter = is_upload ? UploadSurface : DownloadSurface;

    if (!(filter_sys = calloc(1, sizeof(filter_sys_t))))
    {
        msg_Err(obj, "unable to allocate memory");
        return VLC_ENOMEM;
    }
    filter_sys->derive_failed = false;
    filter_sys->image_fallback_failed = false;
    if (is_upload)
    {
        filter_sys->dec_device = vlc_vaapi_FilterHoldInstance(filter,
                                                               &filter_sys->dpy);

        if (filter_sys->dec_device == NULL)
        {
            free(filter_sys);
            return VLC_EGENERIC;
        }

        filter_sys->dest_pics =
            vlc_vaapi_PoolNew(obj, filter_sys->dec_device, filter_sys->dpy,
                              DEST_PICS_POOL_SZ, &filter_sys->va_surface_ids,
                              &filter->fmt_out.video, true);
        if (!filter_sys->dest_pics)
        {
            vlc_vaapi_FilterReleaseInstance(filter, filter_sys->dec_device);
            free(filter_sys);
            return VLC_EGENERIC;
        }
    }
    else
    {
        /* Don't fetch the vaapi instance since it may be not created yet at
         * this point (in case of cpu rendering) */
        filter_sys->dec_device = NULL;
        filter_sys->dpy = NULL;
        filter_sys->dest_pics = NULL;
    }

    if (CopyInitCache(&filter_sys->cache, filter->fmt_in.video.i_width
                      * pixel_bytes))
    {
        if (is_upload)
        {
            picture_pool_Release(filter_sys->dest_pics);
            vlc_vaapi_FilterReleaseInstance(filter, filter_sys->dec_device);
        }
        free(filter_sys);
        return VLC_EGENERIC;
    }

    filter->p_sys = filter_sys;
    msg_Warn(obj, "Using SW chroma filter for %dx%d %4.4s -> %4.4s",
             filter->fmt_in.video.i_width,
             filter->fmt_in.video.i_height,
             (const char *) &filter->fmt_in.video.i_chroma,
             (const char *) &filter->fmt_out.video.i_chroma);

    return VLC_SUCCESS;
}