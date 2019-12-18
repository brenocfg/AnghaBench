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
struct TYPE_5__ {int /*<<< orphan*/  i_planes; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_6__ {int /*<<< orphan*/  buffers; int /*<<< orphan*/  (* DeleteBuffers ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ picture_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pbo_picture_destroy(picture_t *pic)
{
    picture_sys_t *picsys = pic->p_sys;

    picsys->DeleteBuffers(pic->i_planes, picsys->buffers);

    free(picsys);
}