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
struct TYPE_3__ {int bt; } ;
typedef  TYPE_1__ GpBrush ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  BrushTypeHatchFill 132 
#define  BrushTypeLinearGradient 131 
#define  BrushTypePathGradient 130 
#define  BrushTypeSolidColor 129 
#define  BrushTypeTextureFill 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL brush_can_fill_pixels(GpBrush *brush)
{
    switch (brush->bt)
    {
    case BrushTypeSolidColor:
    case BrushTypeHatchFill:
    case BrushTypeLinearGradient:
    case BrushTypeTextureFill:
    case BrushTypePathGradient:
        return TRUE;
    default:
        return FALSE;
    }
}