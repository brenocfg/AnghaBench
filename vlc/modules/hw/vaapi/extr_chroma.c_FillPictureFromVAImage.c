#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_12__ {TYPE_2__ format; } ;
typedef  TYPE_3__ picture_t ;
typedef  int /*<<< orphan*/  copy_cache_t ;
struct TYPE_10__ {int fourcc; } ;
struct TYPE_13__ {size_t const* pitches; int /*<<< orphan*/  height; TYPE_1__ format; int /*<<< orphan*/ * offsets; } ;
typedef  TYPE_4__ VAImage ;

/* Variables and functions */
 int /*<<< orphan*/  Copy420_16_SP_to_P (TYPE_3__*,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy420_SP_to_P (TYPE_3__*,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy420_SP_to_SP (TYPE_3__*,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  VA_FOURCC_NV12 131 
#define  VA_FOURCC_P010 130 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
#define  VLC_CODEC_I420_10L 129 
#define  VLC_CODEC_P010 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static inline void
FillPictureFromVAImage(picture_t *dest,
                       VAImage *src_img, uint8_t *src_buf, copy_cache_t *cache)
{
    const uint8_t * src_planes[2] = { src_buf + src_img->offsets[0],
                                      src_buf + src_img->offsets[1] };
    const size_t    src_pitches[2] = { src_img->pitches[0],
                                       src_img->pitches[1] };

    switch (src_img->format.fourcc)
    {
    case VA_FOURCC_NV12:
    {
        assert(dest->format.i_chroma == VLC_CODEC_I420);
        Copy420_SP_to_P(dest, src_planes, src_pitches, src_img->height, cache);
        break;
    }
    case VA_FOURCC_P010:
        switch (dest->format.i_chroma)
        {
            case VLC_CODEC_P010:
                Copy420_SP_to_SP(dest, src_planes, src_pitches, src_img->height,
                                 cache);
                break;
            case VLC_CODEC_I420_10L:
                Copy420_16_SP_to_P(dest, src_planes, src_pitches,
                                   src_img->height, 6, cache);
                break;
            default:
                vlc_assert_unreachable();
        }
        break;
    default:
        vlc_assert_unreachable();
        break;
    }
}