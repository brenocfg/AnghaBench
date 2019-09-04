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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ bezier_vector ;

/* Variables and functions */
 int /*<<< orphan*/  max (double,double) ; 
 double min (int /*<<< orphan*/ ,double) ; 
 double sqrt (int) ; 

__attribute__((used)) static double bezier_deviation_squared(const bezier_vector *p)
{
    bezier_vector deviation;
    bezier_vector vertex;
    bezier_vector base;
    double base_length;
    double dot;

    vertex.x = (p[0].x + p[1].x*2 + p[2].x)/4 - p[0].x;
    vertex.y = (p[0].y + p[1].y*2 + p[2].y)/4 - p[0].y;

    base.x = p[2].x - p[0].x;
    base.y = p[2].y - p[0].y;

    base_length = sqrt(base.x*base.x + base.y*base.y);
    base.x /= base_length;
    base.y /= base_length;

    dot = base.x*vertex.x + base.y*vertex.y;
    dot = min(max(dot, 0.0), base_length);
    base.x *= dot;
    base.y *= dot;

    deviation.x = vertex.x-base.x;
    deviation.y = vertex.y-base.y;

    return deviation.x*deviation.x + deviation.y*deviation.y;
}