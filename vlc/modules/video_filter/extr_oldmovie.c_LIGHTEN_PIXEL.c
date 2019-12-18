#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_1__ plane_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t PIX_OFS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline void LIGHTEN_PIXEL(int32_t i_x, int32_t i_y,
                                int16_t intensity, plane_t *ps_plane) {
    ADD_MAX( ps_plane->p_pixels[ PIX_OFS(i_x, i_y, ps_plane) ],
        intensity, 0xFF );
}