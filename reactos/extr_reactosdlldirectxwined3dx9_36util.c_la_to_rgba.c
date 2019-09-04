#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vec4 {int /*<<< orphan*/  w; int /*<<< orphan*/  x; int /*<<< orphan*/  z; int /*<<< orphan*/  y; } ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;

/* Variables and functions */

__attribute__((used)) static void la_to_rgba(const struct vec4 *la, struct vec4 *rgba, const PALETTEENTRY *palette)
{
    rgba->x = la->x;
    rgba->y = la->x;
    rgba->z = la->x;
    rgba->w = la->w;
}