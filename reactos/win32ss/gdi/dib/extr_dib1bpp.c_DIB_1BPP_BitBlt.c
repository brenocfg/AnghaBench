#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_21__ {int lDelta; scalar_t__ pvScan0; } ;
struct TYPE_15__ {int cy; int cx; } ;
struct TYPE_20__ {TYPE_2__ sizlBitmap; } ;
struct TYPE_14__ {int y; int x; } ;
struct TYPE_18__ {int right; int left; int top; int bottom; } ;
struct TYPE_17__ {int y; int x; } ;
struct TYPE_19__ {TYPE_7__* PatternSurface; int /*<<< orphan*/  Rop4; TYPE_9__* DestSurface; TYPE_1__ BrushOrigin; int /*<<< orphan*/  XlateSourceToDest; int /*<<< orphan*/  SourceSurface; TYPE_5__ DestRect; TYPE_4__ SourcePoint; TYPE_3__* Brush; } ;
struct TYPE_16__ {int iSolidColor; } ;
struct TYPE_13__ {int x; } ;
typedef  int* PULONG ;
typedef  int* PBYTE ;
typedef  TYPE_6__* PBLTINFO ;
typedef  int LONG ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_12__ BrushOrigin ; 
 int /*<<< orphan*/  ColorTranslation ; 
 int DIB_1BPP_GetPixel (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  DIB_1BPP_PutPixel (TYPE_9__*,int,int,int) ; 
 int DIB_DoRop (int /*<<< orphan*/ ,int,int,int) ; 
 int DIB_GetSource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int DIB_GetSourceIndex (TYPE_7__*,int,int) ; 
 int NoBits ; 
 TYPE_7__* PatternObj ; 
 int PatternWidth ; 
 scalar_t__ ROP4_USES_PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ ROP4_USES_SOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SourceSurf ; 
 scalar_t__ TRUE ; 
 int X ; 
 int k ; 

BOOLEAN
DIB_1BPP_BitBlt(PBLTINFO BltInfo)
{
  LONG DestX, DestY;
  LONG SourceX, SourceY;
  LONG PatternY = 0;
  ULONG Dest, Source = 0, Pattern = 0;
  ULONG Index;
  BOOLEAN UsesSource;
  BOOLEAN UsesPattern;
  PULONG DestBits;
  LONG RoundedRight;

  UsesSource = ROP4_USES_SOURCE(BltInfo->Rop4);
  UsesPattern = ROP4_USES_PATTERN(BltInfo->Rop4);

  RoundedRight = BltInfo->DestRect.right -
    ((BltInfo->DestRect.right - BltInfo->DestRect.left) & 31);
  SourceY = BltInfo->SourcePoint.y;

  if (UsesPattern)
  {
    if (BltInfo->PatternSurface)
    {
      PatternY = (BltInfo->DestRect.top + BltInfo->BrushOrigin.y) %
        BltInfo->PatternSurface->sizlBitmap.cy;
    }
    else
    {
      /* FIXME: Shouldn't it be expanded? */
      if (BltInfo->Brush)
        Pattern = BltInfo->Brush->iSolidColor;
    }
  }

  for (DestY = BltInfo->DestRect.top; DestY < BltInfo->DestRect.bottom; DestY++)
  {
    DestX = BltInfo->DestRect.left;
    SourceX = BltInfo->SourcePoint.x;
    DestBits = (PULONG)(
      (PBYTE)BltInfo->DestSurface->pvScan0 +
      (BltInfo->DestRect.left >> 3) +
      DestY * BltInfo->DestSurface->lDelta);

    if (DestX & 31)
    {
#if 0
      /* FIXME: This case is completely untested!!! */

      Dest = *((PBYTE)DestBits);
      NoBits = 31 - (DestX & 31);

      if (UsesSource)
      {
        Source = 0;
        /* FIXME: This is incorrect! */
        for (Index = 31 - NoBits; Index >= 0; Index++)
          Source |= (DIB_GetSource(SourceSurf, SourceX + Index, SourceY, ColorTranslation) << (31 - Index));
      }

      if (BltInfo->PatternSurface)
      {
        Pattern = 0;
        for (k = 31 - NoBits; k >= 0; k++)
          Pattern |= (DIB_GetSourceIndex(PatternObj, (X + BrushOrigin.x + k) % PatternWidth, PatternY) << (31 - k));
      }

      Dest = DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern);
      Dest &= ~((1 << (31 - NoBits)) - 1);
      Dest |= *((PBYTE)DestBits) & ((1 << (31 - NoBits)) - 1);

      *DestBits = Dest;

      DestX += NoBits;
      SourceX += NoBits;
#endif
    }

    for (; DestX < RoundedRight; DestX += 32, DestBits++, SourceX += 32)
    {
      Dest = *DestBits;

      if (UsesSource)
      {
        Source = 0;
        for (Index = 0; Index < 8; Index++)
        {
          Source |= DIB_GetSource(BltInfo->SourceSurface, SourceX + Index, SourceY, BltInfo->XlateSourceToDest) << (7 - Index);
          Source |= DIB_GetSource(BltInfo->SourceSurface, SourceX + Index + 8, SourceY, BltInfo->XlateSourceToDest) << (8 + (7 - Index));
          Source |= DIB_GetSource(BltInfo->SourceSurface, SourceX + Index + 16, SourceY, BltInfo->XlateSourceToDest) << (16 + (7 - Index));
          Source |= DIB_GetSource(BltInfo->SourceSurface, SourceX + Index + 24, SourceY, BltInfo->XlateSourceToDest) << (24 + (7 - Index));
        }
      }

      if (BltInfo->PatternSurface)
      {
        Pattern = 0;
        for (Index = 0; Index < 8; Index++)
        {
          Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + Index) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << (7 - Index);
          Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + Index + 8) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << (8 + (7 - Index));
          Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + Index + 16) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << (16 + (7 - Index));
          Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + Index + 24) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << (24 + (7 - Index));
        }
      }

      *DestBits = DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern);
    }

    if (DestX < BltInfo->DestRect.right)
    {
      for (; DestX < BltInfo->DestRect.right; DestX++, SourceX++)
      {
        Dest = DIB_1BPP_GetPixel(BltInfo->DestSurface, DestX, DestY);

        if (UsesSource)
        {
          Source = DIB_GetSource(BltInfo->SourceSurface, SourceX, SourceY, BltInfo->XlateSourceToDest);
        }

        if (BltInfo->PatternSurface)
        {
          Pattern = DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY);
        }

        DIB_1BPP_PutPixel(BltInfo->DestSurface, DestX, DestY, DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern) & 0xF);
      }
    }

    SourceY++;
    if (BltInfo->PatternSurface)
    {
      PatternY++;
      PatternY %= BltInfo->PatternSurface->sizlBitmap.cy;
    }
  }

  return TRUE;
}