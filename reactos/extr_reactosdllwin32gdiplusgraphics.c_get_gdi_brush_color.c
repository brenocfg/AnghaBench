#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int bt; } ;
struct TYPE_10__ {int /*<<< orphan*/  forecol; } ;
struct TYPE_9__ {int /*<<< orphan*/  startcolor; } ;
struct TYPE_8__ {int /*<<< orphan*/  centercolor; } ;
struct TYPE_7__ {int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ GpSolidFill ;
typedef  TYPE_2__ GpPathGradient ;
typedef  TYPE_3__ GpLineGradient ;
typedef  TYPE_4__ GpHatch ;
typedef  TYPE_5__ GpBrush ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  ARGB2COLORREF (int /*<<< orphan*/ ) ; 
#define  BrushTypeHatchFill 131 
#define  BrushTypeLinearGradient 130 
#define  BrushTypePathGradient 129 
#define  BrushTypeSolidColor 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static COLORREF get_gdi_brush_color(const GpBrush *brush)
{
    ARGB argb;

    switch (brush->bt)
    {
        case BrushTypeSolidColor:
        {
            const GpSolidFill *sf = (const GpSolidFill *)brush;
            argb = sf->color;
            break;
        }
        case BrushTypeHatchFill:
        {
            const GpHatch *hatch = (const GpHatch *)brush;
            argb = hatch->forecol;
            break;
        }
        case BrushTypeLinearGradient:
        {
            const GpLineGradient *line = (const GpLineGradient *)brush;
            argb = line->startcolor;
            break;
        }
        case BrushTypePathGradient:
        {
            const GpPathGradient *grad = (const GpPathGradient *)brush;
            argb = grad->centercolor;
            break;
        }
        default:
            FIXME("unhandled brush type %d\n", brush->bt);
            argb = 0;
            break;
    }
    return ARGB2COLORREF(argb);
}