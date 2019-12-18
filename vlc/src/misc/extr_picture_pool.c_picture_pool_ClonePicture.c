#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int i_planes; int /*<<< orphan*/  format; TYPE_2__* p; int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_17__ {TYPE_1__* p; int /*<<< orphan*/  pf_destroy; int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_5__ picture_resource_t ;
struct TYPE_15__ {void* opaque; } ;
struct TYPE_18__ {TYPE_3__ gc; } ;
typedef  TYPE_6__ picture_priv_t ;
struct TYPE_19__ {TYPE_4__** picture; } ;
typedef  TYPE_7__ picture_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; int /*<<< orphan*/  p_pixels; } ;
struct TYPE_13__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Hold (TYPE_4__*) ; 
 TYPE_4__* picture_NewFromResource (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  picture_pool_ReleasePicture ; 

__attribute__((used)) static picture_t *picture_pool_ClonePicture(picture_pool_t *pool,
                                            unsigned offset)
{
    picture_t *picture = pool->picture[offset];
    uintptr_t sys = ((uintptr_t)pool) + offset;
    picture_resource_t res = {
        .p_sys = picture->p_sys,
        .pf_destroy = picture_pool_ReleasePicture,
    };

    for (int i = 0; i < picture->i_planes; i++) {
        res.p[i].p_pixels = picture->p[i].p_pixels;
        res.p[i].i_lines = picture->p[i].i_lines;
        res.p[i].i_pitch = picture->p[i].i_pitch;
    }

    picture_t *clone = picture_NewFromResource(&picture->format, &res);
    if (likely(clone != NULL)) {
        ((picture_priv_t *)clone)->gc.opaque = (void *)sys;
        picture_Hold(picture);
    }
    return clone;
}