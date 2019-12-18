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
typedef  int /*<<< orphan*/  spu_scale_t ;
struct TYPE_3__ {int x; int y; int width; int height; int /*<<< orphan*/  scale; } ;
typedef  TYPE_1__ spu_area_t ;

/* Variables and functions */

__attribute__((used)) static spu_area_t spu_area_create(int x, int y, int w, int h, spu_scale_t s)
{
    spu_area_t a = { .x = x, .y = y, .width = w, .height = h, .scale = s };
    return a;
}