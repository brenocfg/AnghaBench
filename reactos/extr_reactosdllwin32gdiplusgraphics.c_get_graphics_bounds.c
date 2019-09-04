#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ hdc; } ;
struct TYPE_11__ {scalar_t__ X; scalar_t__ Y; } ;
struct TYPE_10__ {scalar_t__ X; scalar_t__ Y; scalar_t__ Width; scalar_t__ Height; } ;
typedef  scalar_t__ GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  TYPE_3__ GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CoordinateSpaceDevice ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  WineCoordinateSpaceGdiDevice ; 
 int /*<<< orphan*/  gdip_transform_points (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ get_graphics_device_bounds (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static GpStatus get_graphics_bounds(GpGraphics* graphics, GpRectF* rect)
{
    GpStatus stat = get_graphics_device_bounds(graphics, rect);

    if (stat == Ok && graphics->hdc)
    {
        GpPointF points[4], min_point, max_point;
        int i;

        points[0].X = points[2].X = rect->X;
        points[0].Y = points[1].Y = rect->Y;
        points[1].X = points[3].X = rect->X + rect->Width;
        points[2].Y = points[3].Y = rect->Y + rect->Height;

        gdip_transform_points(graphics, CoordinateSpaceDevice, WineCoordinateSpaceGdiDevice, points, 4);

        min_point = max_point = points[0];

        for (i=1; i<4; i++)
        {
            if (points[i].X < min_point.X) min_point.X = points[i].X;
            if (points[i].Y < min_point.Y) min_point.Y = points[i].Y;
            if (points[i].X > max_point.X) max_point.X = points[i].X;
            if (points[i].Y > max_point.Y) max_point.Y = points[i].Y;
        }

        rect->X = min_point.X;
        rect->Y = min_point.Y;
        rect->Width = max_point.X - min_point.X;
        rect->Height = max_point.Y - min_point.Y;
    }

    return stat;
}