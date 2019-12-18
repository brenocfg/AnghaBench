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

/* Variables and functions */
 int BAR_MAX_HEIGHT ; 
 int /*<<< orphan*/  glColor4f (float,float,float,float) ; 

__attribute__((used)) static void setBarColor(float f_height)
{
    float r, b;

#define BAR_MAX_HEIGHT 4.2f
    r = -1.f + 2 / BAR_MAX_HEIGHT * f_height;
    b = 2.f - 2 / BAR_MAX_HEIGHT * f_height;
#undef BAR_MAX_HEIGHT

    /* Test the ranges. */
    r = r > 1.f ? 1.f : r;
    b = b > 1.f ? 1.f : b;

    r = r < 0.f ? 0.f : r;
    b = b < 0.f ? 0.f : b;

    /* Set the bar color. */
    glColor4f(r, 0.f, b, 1.f);
}