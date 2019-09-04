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
struct TYPE_3__ {double X; double Y; double Width; double Height; } ;
typedef  TYPE_1__ RectF ;

/* Variables and functions */

__attribute__((used)) static void set_rect_empty(RectF *rc)
{
    rc->X = 0.0;
    rc->Y = 0.0;
    rc->Width = 0.0;
    rc->Height = 0.0;
}