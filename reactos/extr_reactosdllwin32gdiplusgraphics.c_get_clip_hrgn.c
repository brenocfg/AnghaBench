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
struct TYPE_4__ {scalar_t__ gdi_clip; int /*<<< orphan*/  clip; } ;
typedef  scalar_t__ HRGN ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  TYPE_1__ GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoordinateSpaceDevice ; 
 scalar_t__ CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GdipCloneRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetRegionHRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GdipIsMatrixIdentity (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GdipTransformRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  RGN_COPY ; 
 int /*<<< orphan*/  WineCoordinateSpaceGdiDevice ; 
 scalar_t__ get_graphics_transform (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GpStatus get_clip_hrgn(GpGraphics *graphics, HRGN *hrgn)
{
    GpRegion *rgn;
    GpMatrix transform;
    GpStatus stat;
    BOOL identity;

    stat = get_graphics_transform(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceDevice, &transform);

    if (stat == Ok)
        stat = GdipIsMatrixIdentity(&transform, &identity);

    if (stat == Ok)
        stat = GdipCloneRegion(graphics->clip, &rgn);

    if (stat == Ok)
    {
        if (!identity)
            stat = GdipTransformRegion(rgn, &transform);

        if (stat == Ok)
            stat = GdipGetRegionHRgn(rgn, NULL, hrgn);

        GdipDeleteRegion(rgn);
    }

    if (stat == Ok && graphics->gdi_clip)
    {
        if (*hrgn)
            CombineRgn(*hrgn, *hrgn, graphics->gdi_clip, RGN_AND);
        else
        {
            *hrgn = CreateRectRgn(0,0,0,0);
            CombineRgn(*hrgn, graphics->gdi_clip, graphics->gdi_clip, RGN_COPY);
        }
    }

    return stat;
}