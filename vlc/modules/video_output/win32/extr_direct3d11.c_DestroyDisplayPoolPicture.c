#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ picture_t ;
typedef  int /*<<< orphan*/  picture_sys_d3d11_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseD3D11PictureSys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DestroyDisplayPoolPicture(picture_t *picture)
{
    picture_sys_d3d11_t *p_sys = picture->p_sys;
    ReleaseD3D11PictureSys( p_sys );
    free(p_sys);
}