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
struct TYPE_3__ {int f_fovx; int f_fovy; float f_z; } ;
typedef  TYPE_1__ vout_display_opengl_t ;

/* Variables and functions */
 float const FIELD_OF_VIEW_DEGREES_MAX ; 
 float const M_PI ; 
 float SPHERE_RADIUS ; 
 int /*<<< orphan*/  atanf (int /*<<< orphan*/ ) ; 
 float sinf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrtf (float) ; 
 float tanf (int) ; 

__attribute__((used)) static void UpdateZ(vout_display_opengl_t *vgl)
{
    /* Do trigonometry to calculate the minimal z value
     * that will allow us to zoom out without seeing the outside of the
     * sphere (black borders). */
    float tan_fovx_2 = tanf(vgl->f_fovx / 2);
    float tan_fovy_2 = tanf(vgl->f_fovy / 2);
    float z_min = - SPHERE_RADIUS / sinf(atanf(sqrtf(
                    tan_fovx_2 * tan_fovx_2 + tan_fovy_2 * tan_fovy_2)));

    /* The FOV value above which z is dynamically calculated. */
    const float z_thresh = 90.f;

    if (vgl->f_fovx <= z_thresh * M_PI / 180)
        vgl->f_z = 0;
    else
    {
        float f = z_min / ((FIELD_OF_VIEW_DEGREES_MAX - z_thresh) * M_PI / 180);
        vgl->f_z = f * vgl->f_fovx - f * z_thresh * M_PI / 180;
        if (vgl->f_z < z_min)
            vgl->f_z = z_min;
    }
}