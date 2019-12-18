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
typedef  int /*<<< orphan*/  XLATEOBJ ;
typedef  int /*<<< orphan*/  SURFOBJ ;
typedef  int /*<<< orphan*/  ROP4 ;
typedef  int /*<<< orphan*/  RECTL ;
typedef  int /*<<< orphan*/  POINTL ;
typedef  int /*<<< orphan*/  BRUSHOBJ ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

BOOLEAN Dummy_StretchBlt(SURFOBJ *DestSurf, SURFOBJ *SourceSurf,
                         SURFOBJ *PatternSurface, SURFOBJ *MaskSurf,
                         RECTL*  DestRect,  RECTL  *SourceRect,
                         POINTL* MaskOrigin, BRUSHOBJ* Brush,
                         POINTL* BrushOrign,
                         XLATEOBJ *ColorTranslation,
                         ROP4 Rop)
{
  return FALSE;
}