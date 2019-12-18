#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int i_planes; TYPE_7__* context; int /*<<< orphan*/  format; TYPE_2__* p; int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_18__ {TYPE_1__* p; int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_5__ picture_resource_t ;
struct TYPE_16__ {TYPE_4__* opaque; } ;
struct TYPE_19__ {TYPE_3__ gc; } ;
typedef  TYPE_6__ picture_priv_t ;
struct TYPE_20__ {TYPE_7__* (* copy ) (TYPE_7__*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; int /*<<< orphan*/  p_pixels; } ;
struct TYPE_14__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_DestroyClone ; 
 int /*<<< orphan*/  picture_Hold (TYPE_4__*) ; 
 TYPE_4__* picture_NewFromResource (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_7__* stub1 (TYPE_7__*) ; 

picture_t *picture_Clone(picture_t *picture)
{
    /* TODO: merge common code with picture_pool_ClonePicture(). */
    picture_resource_t res = {
        .p_sys = picture->p_sys,
        .pf_destroy = picture_DestroyClone,
    };

    for (int i = 0; i < picture->i_planes; i++) {
        res.p[i].p_pixels = picture->p[i].p_pixels;
        res.p[i].i_lines = picture->p[i].i_lines;
        res.p[i].i_pitch = picture->p[i].i_pitch;
    }

    picture_t *clone = picture_NewFromResource(&picture->format, &res);
    if (likely(clone != NULL)) {
        ((picture_priv_t *)clone)->gc.opaque = picture;
        picture_Hold(picture);

        if (picture->context != NULL)
            clone->context = picture->context->copy(picture->context);
    }
    return clone;
}