#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_13__ {int /*<<< orphan*/ * context; TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;

/* Variables and functions */
#define  VLC_CODEC_BGRA 132 
 int VLC_CODEC_CVPX_BGRA ; 
 int VLC_CODEC_CVPX_I420 ; 
 int VLC_CODEC_CVPX_NV12 ; 
 int VLC_CODEC_CVPX_P010 ; 
 int VLC_CODEC_CVPX_UYVY ; 
#define  VLC_CODEC_I420 131 
#define  VLC_CODEC_NV12 130 
#define  VLC_CODEC_P010 129 
#define  VLC_CODEC_UYVY 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cvpxpic_attach (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvpxpic_get_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_CopyProperties (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* picture_NewFromFormat (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_2__*) ; 

picture_t *
cvpxpic_unmap(picture_t *mapped_pic)
{
    video_format_t fmt = mapped_pic->format;
    switch (fmt.i_chroma)
    {
        case VLC_CODEC_UYVY: fmt.i_chroma = VLC_CODEC_CVPX_UYVY; break;
        case VLC_CODEC_NV12: fmt.i_chroma = VLC_CODEC_CVPX_NV12; break;
        case VLC_CODEC_P010: fmt.i_chroma = VLC_CODEC_CVPX_P010; break;
        case VLC_CODEC_I420: fmt.i_chroma = VLC_CODEC_CVPX_I420; break;
        case VLC_CODEC_BGRA: fmt.i_chroma = VLC_CODEC_CVPX_BGRA; break;
        default:
            assert(!"invalid mapped_pic fmt");
            picture_Release(mapped_pic);
            return NULL;
    }
    assert(mapped_pic->context != NULL);

    picture_t *hw_pic = picture_NewFromFormat(&fmt);
    if (hw_pic == NULL)
    {
        picture_Release(mapped_pic);
        return NULL;
    }

    cvpxpic_attach(hw_pic, cvpxpic_get_ref(mapped_pic));
    picture_CopyProperties(hw_pic, mapped_pic);
    picture_Release(mapped_pic);
    return hw_pic;
}