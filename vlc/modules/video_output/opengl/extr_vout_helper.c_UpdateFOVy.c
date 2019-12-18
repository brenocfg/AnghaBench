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
struct TYPE_3__ {int f_fovy; int f_fovx; int f_sar; } ;
typedef  TYPE_1__ vout_display_opengl_t ;

/* Variables and functions */
 int atanf (int) ; 
 int tanf (int) ; 

__attribute__((used)) static void UpdateFOVy(vout_display_opengl_t *vgl)
{
    vgl->f_fovy = 2 * atanf(tanf(vgl->f_fovx / 2) / vgl->f_sar);
}