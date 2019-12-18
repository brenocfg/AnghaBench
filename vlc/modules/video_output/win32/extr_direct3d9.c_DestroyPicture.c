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
struct TYPE_3__ {int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_1__ picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseD3D9PictureSys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DestroyPicture(picture_t *picture)
{
    ReleaseD3D9PictureSys(picture->p_sys);

    free(picture->p_sys);
}