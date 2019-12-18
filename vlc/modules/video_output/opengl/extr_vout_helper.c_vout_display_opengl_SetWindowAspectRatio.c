#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  projection_mode; } ;
struct TYPE_8__ {float f_sar; int /*<<< orphan*/  prgm; TYPE_1__ fmt; } ;
typedef  TYPE_2__ vout_display_opengl_t ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateFOVy (TYPE_2__*) ; 
 int /*<<< orphan*/  UpdateZ (TYPE_2__*) ; 
 int /*<<< orphan*/  getViewpointMatrixes (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vout_display_opengl_SetWindowAspectRatio(vout_display_opengl_t *vgl,
                                              float f_sar)
{
    /* Each time the window size changes, we must recompute the minimum zoom
     * since the aspect ration changes.
     * We must also set the new current zoom value. */
    vgl->f_sar = f_sar;
    UpdateFOVy(vgl);
    UpdateZ(vgl);
    getViewpointMatrixes(vgl, vgl->fmt.projection_mode, vgl->prgm);
}