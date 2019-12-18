#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int i_width; int i_height; } ;
struct TYPE_11__ {TYPE_5__ format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_12__ {scalar_t__ p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_10__ {scalar_t__ p_pic; } ;
struct TYPE_13__ {int i_frames; int i_ratio; int i_width; int i_height; TYPE_1__ scene; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SavePicture (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  picture_Copy (scalar_t__,TYPE_2__*) ; 
 scalar_t__ picture_NewFromFormat (TYPE_5__*) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 

__attribute__((used)) static void SnapshotRatio( filter_t *p_filter, picture_t *p_pic )
{
    filter_sys_t *p_sys = (filter_sys_t *)p_filter->p_sys;

    if( !p_pic ) return;

    if( p_sys->i_frames % p_sys->i_ratio != 0 )
    {
        p_sys->i_frames++;
        return;
    }
    p_sys->i_frames++;

    if( p_sys->scene.p_pic )
        picture_Release( p_sys->scene.p_pic );

    if( (p_sys->i_width <= 0) && (p_sys->i_height > 0) )
    {
        p_sys->i_width = (p_pic->format.i_width * p_sys->i_height) / p_pic->format.i_height;
    }
    else if( (p_sys->i_height <= 0) && (p_sys->i_width > 0) )
    {
        p_sys->i_height = (p_pic->format.i_height * p_sys->i_width) / p_pic->format.i_width;
    }
    else if( (p_sys->i_width <= 0) && (p_sys->i_height <= 0) )
    {
        p_sys->i_width = p_pic->format.i_width;
        p_sys->i_height = p_pic->format.i_height;
    }

    p_sys->scene.p_pic = picture_NewFromFormat( &p_pic->format );
    if( p_sys->scene.p_pic )
    {
        picture_Copy( p_sys->scene.p_pic, p_pic );
        SavePicture( p_filter, p_sys->scene.p_pic );
    }
}