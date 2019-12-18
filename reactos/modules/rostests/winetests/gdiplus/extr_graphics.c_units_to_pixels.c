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
typedef  double REAL ;
typedef  int GpUnit ;

/* Variables and functions */
#define  UnitDisplay 133 
#define  UnitDocument 132 
#define  UnitInch 131 
#define  UnitMillimeter 130 
#define  UnitPixel 129 
#define  UnitPoint 128 
 double mm_per_inch ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int) ; 
 double point_per_inch ; 

__attribute__((used)) static REAL units_to_pixels(REAL units, GpUnit unit, REAL dpi)
{
    switch (unit)
    {
    case UnitPixel:
    case UnitDisplay:
        return units;
    case UnitPoint:
        return units * dpi / point_per_inch;
    case UnitInch:
        return units * dpi;
    case UnitDocument:
        return units * dpi / 300.0; /* Per MSDN */
    case UnitMillimeter:
        return units * dpi / mm_per_inch;
    default:
        ok(0, "Unsupported unit: %d\n", unit);
        return 0;
    }
}