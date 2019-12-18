#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int i_chroma; } ;
struct TYPE_18__ {TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_19__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_20__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 TYPE_2__* CopyInfoAndRelease (TYPE_2__*,TYPE_2__*) ; 
#define  VLC_CODEC_I420 130 
#define  VLC_CODEC_J420 129 
#define  VLC_CODEC_YV12 128 
 int /*<<< orphan*/  combine_side_by_side_yuv420 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* filter_NewPicture (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_2__*) ; 

__attribute__((used)) static picture_t *Filter(filter_t *p_filter, picture_t *p_pic)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if (!p_pic)
        return NULL;

    picture_t *p_outpic = filter_NewPicture(p_filter);
    if (!p_outpic)
    {
        picture_Release(p_pic);
        return NULL;
    }

    switch (p_pic->format.i_chroma)
    {
        case VLC_CODEC_I420:
        case VLC_CODEC_J420:
        case VLC_CODEC_YV12:
            combine_side_by_side_yuv420(p_pic, p_outpic,
                                        p_sys->left, p_sys->right);
            break;

        default:
            msg_Warn(p_filter, "Unsupported input chroma (%4.4s)",
                     (char*)&(p_pic->format.i_chroma));
            picture_Release(p_pic);
            return NULL;
    }

    return CopyInfoAndRelease(p_outpic, p_pic);
}