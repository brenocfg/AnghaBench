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
typedef  int /*<<< orphan*/  GpPenType ;
typedef  int GpBrushType ;

/* Variables and functions */
#define  BrushTypeHatchFill 132 
#define  BrushTypeLinearGradient 131 
#define  BrushTypePathGradient 130 
#define  BrushTypeSolidColor 129 
#define  BrushTypeTextureFill 128 
 int /*<<< orphan*/  PenTypeHatchFill ; 
 int /*<<< orphan*/  PenTypeLinearGradient ; 
 int /*<<< orphan*/  PenTypePathGradient ; 
 int /*<<< orphan*/  PenTypeSolidColor ; 
 int /*<<< orphan*/  PenTypeTextureFill ; 
 int /*<<< orphan*/  PenTypeUnknown ; 

__attribute__((used)) static GpPenType bt_to_pt(GpBrushType bt)
{
    switch(bt){
        case BrushTypeSolidColor:
            return PenTypeSolidColor;
        case BrushTypeHatchFill:
            return PenTypeHatchFill;
        case BrushTypeTextureFill:
            return PenTypeTextureFill;
        case BrushTypePathGradient:
            return PenTypePathGradient;
        case BrushTypeLinearGradient:
            return PenTypeLinearGradient;
        default:
            return PenTypeUnknown;
    }
}