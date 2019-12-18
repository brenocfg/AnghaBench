#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {unsigned int i_pitch; scalar_t__ i_lines; scalar_t__ i_visible_pitch; scalar_t__ i_visible_lines; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_6__ {scalar_t__ i_height; scalar_t__ i_chroma; } ;
struct TYPE_8__ {int i_planes; TYPE_1__ format; TYPE_2__* p; } ;
typedef  TYPE_3__ picture_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_I420 ; 
 scalar_t__ VLC_CODEC_J420 ; 
 scalar_t__ VLC_CODEC_NV12 ; 
 scalar_t__ VLC_CODEC_NV21 ; 
 scalar_t__ VLC_CODEC_P010 ; 
 scalar_t__ VLC_CODEC_YV12 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  picture_SwapUV (TYPE_3__*) ; 
 scalar_t__ vlc_fourcc_AreUVPlanesSwapped (scalar_t__,scalar_t__) ; 

int picture_UpdatePlanes(picture_t *picture, uint8_t *data, unsigned pitch)
{
    /* fill in buffer info in first plane */
    picture->p->p_pixels = data;
    picture->p->i_pitch  = pitch;
    picture->p->i_lines  = picture->format.i_height;
    assert(picture->p->i_visible_pitch <= picture->p->i_pitch);
    assert(picture->p->i_visible_lines <= picture->p->i_lines);

    /*  Fill chroma planes for biplanar YUV */
    if (picture->format.i_chroma == VLC_CODEC_NV12 ||
        picture->format.i_chroma == VLC_CODEC_NV21 ||
        picture->format.i_chroma == VLC_CODEC_P010) {

        for (int n = 1; n < picture->i_planes; n++) {
            const plane_t *o = &picture->p[n-1];
            plane_t *p = &picture->p[n];

            p->p_pixels = o->p_pixels + o->i_lines * o->i_pitch;
            p->i_pitch  = pitch;
            p->i_lines  = picture->format.i_height / 2;
            assert(p->i_visible_pitch <= p->i_pitch);
            assert(p->i_visible_lines <= p->i_lines);
        }
        /* The dx/d3d buffer is always allocated as NV12 */
        if (vlc_fourcc_AreUVPlanesSwapped(picture->format.i_chroma, VLC_CODEC_NV12)) {
            /* TODO : Swap NV21 UV planes to match NV12 */
            return VLC_EGENERIC;
        }
    }

    /*  Fill chroma planes for planar YUV */
    else
    if (picture->format.i_chroma == VLC_CODEC_I420 ||
        picture->format.i_chroma == VLC_CODEC_J420 ||
        picture->format.i_chroma == VLC_CODEC_YV12) {

        for (int n = 1; n < picture->i_planes; n++) {
            const plane_t *o = &picture->p[n-1];
            plane_t *p = &picture->p[n];

            p->p_pixels = o->p_pixels + o->i_lines * o->i_pitch;
            p->i_pitch  = pitch / 2;
            p->i_lines  = picture->format.i_height / 2;
        }
        /* The dx/d3d buffer is always allocated as YV12 */
        if (vlc_fourcc_AreUVPlanesSwapped(picture->format.i_chroma, VLC_CODEC_YV12))
            picture_SwapUV( picture );
    }
    return VLC_SUCCESS;
}