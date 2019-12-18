#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_to_be_freed; scalar_t__ i_cv_image_size; int /*<<< orphan*/ ** p_cv_image; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int VOUT_MAX_PLANES ; 
 int /*<<< orphan*/  cvReleaseImageHeader (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ReleaseImages( filter_t* p_filter )
{
    filter_sys_t* p_sys = p_filter->p_sys;

    for( int i = 0; i < VOUT_MAX_PLANES; i++ )
    {
        if (p_sys->p_cv_image[i] != NULL)
        {
            cvReleaseImageHeader(&(p_sys->p_cv_image[i]));
            p_sys->p_cv_image[i] = NULL;
        }
    }
    p_sys->i_cv_image_size = 0;

    /* Release temp picture_t if it exists */
    if (p_sys->p_to_be_freed)
    {
        picture_Release( p_sys->p_to_be_freed );
        p_sys->p_to_be_freed = NULL;
    }

#ifndef NDEBUG
    msg_Dbg( p_filter, "images released" );
#endif
}