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
typedef  int UINT ;
struct TYPE_3__ {int right; int bottom; } ;
typedef  TYPE_1__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  GdipGetImageHeight (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GdipGetImageWidth (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ZoomPercents ; 
 int /*<<< orphan*/  hDispWnd ; 
 int /*<<< orphan*/  image ; 

__attribute__((used)) static void ResetZoom(void)
{
    RECT Rect;
    UINT ImageWidth, ImageHeight;

    /* get disp window size and image size */
    GetClientRect(hDispWnd, &Rect);
    GdipGetImageWidth(image, &ImageWidth);
    GdipGetImageHeight(image, &ImageHeight);

    /* compare two aspect rates. same as
       (ImageHeight / ImageWidth < Rect.bottom / Rect.right) in real */
    if (ImageHeight * Rect.right < Rect.bottom * ImageWidth)
    {
        if (Rect.right < ImageWidth)
        {
            /* it's large, shrink it */
            ZoomPercents = (Rect.right * 100) / ImageWidth;
        }
        else
        {
            /* it's small. show as original size */
            ZoomPercents = 100;
        }
    }
    else
    {
        if (Rect.bottom < ImageHeight)
        {
            /* it's large, shrink it */
            ZoomPercents = (Rect.bottom * 100) / ImageHeight;
        }
        else
        {
            /* it's small. show as original size */
            ZoomPercents = 100;
        }
    }
}