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
struct TYPE_4__ {int X; int Y; } ;
typedef  int REAL ;
typedef  TYPE_1__ GpPointF ;

/* Variables and functions */

__attribute__((used)) static REAL intersect_line_scanline(const GpPointF *p1, const GpPointF *p2, REAL y)
{
    return (p1->X - p2->X) * (p2->Y - y) / (p2->Y - p1->Y) + p2->X;
}