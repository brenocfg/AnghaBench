#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_7__ {int /*<<< orphan*/  snapshot; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_PNG ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ image_Type2Fourcc (char const*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 scalar_t__ picture_Export (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int const,int const,int) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int var_InheritInteger (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * vout_snapshot_Get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vout_GetSnapshot(vout_thread_t *vout,
                     block_t **image_dst, picture_t **picture_dst,
                     video_format_t *fmt,
                     const char *type, vlc_tick_t timeout)
{
    assert(!vout->p->dummy);
    picture_t *picture = vout_snapshot_Get(vout->p->snapshot, timeout);
    if (!picture) {
        msg_Err(vout, "Failed to grab a snapshot");
        return VLC_EGENERIC;
    }

    if (image_dst) {
        vlc_fourcc_t codec = VLC_CODEC_PNG;
        if (type && image_Type2Fourcc(type))
            codec = image_Type2Fourcc(type);

        const int override_width  = var_InheritInteger(vout, "snapshot-width");
        const int override_height = var_InheritInteger(vout, "snapshot-height");

        if (picture_Export(VLC_OBJECT(vout), image_dst, fmt,
                           picture, codec, override_width, override_height, false)) {
            msg_Err(vout, "Failed to convert image for snapshot");
            picture_Release(picture);
            return VLC_EGENERIC;
        }
    }
    if (picture_dst)
        *picture_dst = picture;
    else
        picture_Release(picture);
    return VLC_SUCCESS;
}