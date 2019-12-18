#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_5__ {scalar_t__ p_pic; } ;
struct TYPE_7__ {struct TYPE_7__* psz_path; struct TYPE_7__* psz_prefix; struct TYPE_7__* psz_format; TYPE_1__ scene; int /*<<< orphan*/  p_image; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 

__attribute__((used)) static void Destroy( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    filter_sys_t *p_sys = p_filter->p_sys;

    image_HandlerDelete( p_sys->p_image );

    if( p_sys->scene.p_pic )
        picture_Release( p_sys->scene.p_pic );
    free( p_sys->psz_format );
    free( p_sys->psz_prefix );
    free( p_sys->psz_path );
    free( p_sys );
}