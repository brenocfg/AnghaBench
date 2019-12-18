#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct vf_priv_s {int /*<<< orphan*/ * Frame; int /*<<< orphan*/ * Coefs; int /*<<< orphan*/  Line; } ;
struct TYPE_16__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_17__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_18__ {int b_recalc_coefs; int /*<<< orphan*/ * h; int /*<<< orphan*/ * w; int /*<<< orphan*/  coefs_mutex; int /*<<< orphan*/  chroma_temp; int /*<<< orphan*/  chroma_spat; int /*<<< orphan*/  luma_temp; int /*<<< orphan*/  luma_spat; struct vf_priv_s cfg; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 TYPE_2__* CopyInfoAndRelease (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PrecalcCoefs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deNoise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* filter_NewPicture (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *Filter(filter_t *filter, picture_t *src)
{
    picture_t *dst;
    filter_sys_t *sys = filter->p_sys;
    struct vf_priv_s *cfg = &sys->cfg;
    bool recalc = false;

    if (!src) return NULL;

    dst = filter_NewPicture(filter);
    if ( unlikely(!dst) ) {
        picture_Release(src);
        return NULL;
    }
    vlc_mutex_lock( &sys->coefs_mutex );
    recalc = sys->b_recalc_coefs;
    sys->b_recalc_coefs = false;

    if( unlikely( recalc ) )
    {
        msg_Dbg( filter, "Changing coefs to %.2f %.2f %.2f %.2f",
                            sys->luma_spat, sys->luma_temp, sys->chroma_spat, sys->chroma_temp );
        PrecalcCoefs(cfg->Coefs[0], sys->luma_spat);
        PrecalcCoefs(cfg->Coefs[1], sys->luma_temp);
        PrecalcCoefs(cfg->Coefs[2], sys->chroma_spat);
        PrecalcCoefs(cfg->Coefs[3], sys->chroma_temp);
    }
    vlc_mutex_unlock( &sys->coefs_mutex );

    deNoise(src->p[0].p_pixels, dst->p[0].p_pixels,
            cfg->Line, &cfg->Frame[0], sys->w[0], sys->h[0],
            src->p[0].i_pitch, dst->p[0].i_pitch,
            cfg->Coefs[0],
            cfg->Coefs[0],
            cfg->Coefs[1]);
    deNoise(src->p[1].p_pixels, dst->p[1].p_pixels,
            cfg->Line, &cfg->Frame[1], sys->w[1], sys->h[1],
            src->p[1].i_pitch, dst->p[1].i_pitch,
            cfg->Coefs[2],
            cfg->Coefs[2],
            cfg->Coefs[3]);
    deNoise(src->p[2].p_pixels, dst->p[2].p_pixels,
            cfg->Line, &cfg->Frame[2], sys->w[2], sys->h[2],
            src->p[2].i_pitch, dst->p[2].i_pitch,
            cfg->Coefs[2],
            cfg->Coefs[2],
            cfg->Coefs[3]);

    if(unlikely(!cfg->Frame[0] || !cfg->Frame[1] || !cfg->Frame[2]))
    {
        picture_Release( src );
        picture_Release( dst );
        return NULL;
    }

    return CopyInfoAndRelease(dst, src);
}