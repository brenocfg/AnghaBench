#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tmCharSet; scalar_t__ tmStruckOut; scalar_t__ tmUnderlined; scalar_t__ tmItalic; int /*<<< orphan*/  tmWeight; } ;
struct TYPE_11__ {TYPE_1__ otmTextMetrics; } ;
struct TYPE_15__ {scalar_t__ unit; TYPE_3__* family; TYPE_2__ otm; int /*<<< orphan*/  emSize; } ;
struct TYPE_14__ {scalar_t__ unit; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_13__ {double lfHeight; int lfItalic; int lfUnderline; int lfStrikeOut; int /*<<< orphan*/  lfFaceName; scalar_t__ lfPitchAndFamily; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfClipPrecision; int /*<<< orphan*/  lfOutPrecision; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfWeight; scalar_t__ lfOrientation; scalar_t__ lfEscapement; scalar_t__ lfWidth; } ;
struct TYPE_12__ {int /*<<< orphan*/  FamilyName; } ;
typedef  double REAL ;
typedef  TYPE_4__ LOGFONTW ;
typedef  TYPE_5__ GpGraphics ;
typedef  TYPE_6__ GpFont ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 scalar_t__ UnitDisplay ; 
 scalar_t__ UnitPixel ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double units_to_pixels (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void get_log_fontW(const GpFont *font, GpGraphics *graphics, LOGFONTW *lf)
{
    REAL height;

    if (font->unit == UnitPixel)
    {
        height = units_to_pixels(font->emSize, graphics->unit, graphics->yres);
    }
    else
    {
        if (graphics->unit == UnitDisplay || graphics->unit == UnitPixel)
            height = units_to_pixels(font->emSize, font->unit, graphics->xres);
        else
            height = units_to_pixels(font->emSize, font->unit, graphics->yres);
    }

    lf->lfHeight = -(height + 0.5);
    lf->lfWidth = 0;
    lf->lfEscapement = 0;
    lf->lfOrientation = 0;
    lf->lfWeight = font->otm.otmTextMetrics.tmWeight;
    lf->lfItalic = font->otm.otmTextMetrics.tmItalic ? 1 : 0;
    lf->lfUnderline = font->otm.otmTextMetrics.tmUnderlined ? 1 : 0;
    lf->lfStrikeOut = font->otm.otmTextMetrics.tmStruckOut ? 1 : 0;
    lf->lfCharSet = font->otm.otmTextMetrics.tmCharSet;
    lf->lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf->lfQuality = DEFAULT_QUALITY;
    lf->lfPitchAndFamily = 0;
    strcpyW(lf->lfFaceName, font->family->FamilyName);
}