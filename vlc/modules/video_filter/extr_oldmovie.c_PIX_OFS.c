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
struct TYPE_3__ {int i_pixel_pitch; int i_pitch; } ;
typedef  TYPE_1__ plane_t ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static inline int32_t PIX_OFS(int32_t i_x, int32_t i_y, plane_t *ps_plane) {
    return i_x * ps_plane->i_pixel_pitch + i_y * ps_plane->i_pitch; }