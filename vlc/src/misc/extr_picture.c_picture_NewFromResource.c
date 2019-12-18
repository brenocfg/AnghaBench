#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_13__ {int i_planes; TYPE_2__* p; int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_14__ {TYPE_3__* p; int /*<<< orphan*/ * pf_destroy; int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_5__ picture_resource_t ;
struct TYPE_10__ {int /*<<< orphan*/ * destroy; } ;
struct TYPE_15__ {TYPE_1__ gc; TYPE_4__ picture; } ;
typedef  TYPE_6__ picture_priv_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; int /*<<< orphan*/  p_pixels; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_lines; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * picture_DestroyDummy ; 
 TYPE_6__* picture_NewPrivate (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

picture_t *picture_NewFromResource( const video_format_t *p_fmt, const picture_resource_t *p_resource )
{
    assert(p_resource != NULL);

    picture_priv_t *priv = picture_NewPrivate(p_fmt, 0);
    if (unlikely(priv == NULL))
        return NULL;

    picture_t *p_picture = &priv->picture;

    p_picture->p_sys = p_resource->p_sys;

    if( p_resource->pf_destroy != NULL )
        priv->gc.destroy = p_resource->pf_destroy;
    else
        priv->gc.destroy = picture_DestroyDummy;

    for( int i = 0; i < p_picture->i_planes; i++ )
    {
        p_picture->p[i].p_pixels = p_resource->p[i].p_pixels;
        p_picture->p[i].i_lines  = p_resource->p[i].i_lines;
        p_picture->p[i].i_pitch  = p_resource->p[i].i_pitch;
    }

    return p_picture;
}