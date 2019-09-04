#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_18__ {int lDelta; scalar_t__ pvScan0; } ;
struct TYPE_15__ {int cy; int cx; } ;
struct TYPE_17__ {TYPE_5__ sizlBitmap; } ;
struct TYPE_14__ {int y; int x; } ;
struct TYPE_13__ {int right; int left; int top; int bottom; } ;
struct TYPE_12__ {int y; int x; } ;
struct TYPE_16__ {TYPE_7__* PatternSurface; int /*<<< orphan*/  Rop4; TYPE_8__* DestSurface; TYPE_4__ BrushOrigin; int /*<<< orphan*/  XlateSourceToDest; int /*<<< orphan*/  SourceSurface; TYPE_3__ DestRect; TYPE_2__ SourcePoint; TYPE_1__* Brush; } ;
struct TYPE_11__ {size_t iSolidColor; } ;
typedef  int* PULONG ;
typedef  scalar_t__ PBYTE ;
typedef  TYPE_6__* PBLTINFO ;
typedef  int LONG ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int DIB_4BPP_GetPixel (TYPE_8__*,int,int) ; 
 int /*<<< orphan*/  DIB_4BPP_PutPixel (TYPE_8__*,int,int,int) ; 
 int DIB_DoRop (int /*<<< orphan*/ ,int,int,int) ; 
 int DIB_GetSource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int DIB_GetSourceIndex (TYPE_7__*,int,int) ; 
 scalar_t__ ROP4_USES_PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ ROP4_USES_SOURCE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

BOOLEAN
DIB_4BPP_BitBlt(PBLTINFO BltInfo)
{
  LONG DestX, DestY;
  LONG SourceX, SourceY;
  LONG PatternY = 0;
  ULONG Dest, Source = 0, Pattern = 0;
  BOOLEAN UsesSource;
  BOOLEAN UsesPattern;
  PULONG DestBits;
  LONG RoundedRight;
  static const ULONG ExpandSolidColor[16] =
  {
    0x00000000 /* 0 */,
    0x11111111 /* 1 */,
    0x22222222 /* 2 */,
    0x33333333 /* 3 */,
    0x44444444 /* 4 */,
    0x55555555 /* 5 */,
    0x66666666 /* 6 */,
    0x77777777 /* 7 */,
    0x88888888 /* 8 */,
    0x99999999 /* 9 */,
    0xAAAAAAAA /* 10 */,
    0xBBBBBBBB /* 11 */,
    0xCCCCCCCC /* 12 */,
    0xDDDDDDDD /* 13 */,
    0xEEEEEEEE /* 14 */,
    0xFFFFFFFF /* 15 */,
  };

  UsesSource = ROP4_USES_SOURCE(BltInfo->Rop4);
  UsesPattern = ROP4_USES_PATTERN(BltInfo->Rop4);

  SourceY = BltInfo->SourcePoint.y;
  RoundedRight = BltInfo->DestRect.right -
    ((BltInfo->DestRect.right - BltInfo->DestRect.left) & 0x7);

  if (UsesPattern)
  {
    if (BltInfo->PatternSurface)
    {
      PatternY = (BltInfo->DestRect.top + BltInfo->BrushOrigin.y) %
        BltInfo->PatternSurface->sizlBitmap.cy;
    }
    else
    {
      if (BltInfo->Brush)
        Pattern = ExpandSolidColor[BltInfo->Brush->iSolidColor];
    }
  }

  for (DestY = BltInfo->DestRect.top; DestY < BltInfo->DestRect.bottom; DestY++)
  {
    DestBits = (PULONG)(
      (PBYTE)BltInfo->DestSurface->pvScan0 +
      (BltInfo->DestRect.left >> 1) +
      DestY * BltInfo->DestSurface->lDelta);
    SourceX = BltInfo->SourcePoint.x;
    DestX = BltInfo->DestRect.left;

    if (DestX & 0x1)
    {
      Dest = DIB_4BPP_GetPixel(BltInfo->DestSurface, DestX, DestY);

      if (UsesSource)
      {
        Source = DIB_GetSource(BltInfo->SourceSurface, SourceX, SourceY, BltInfo->XlateSourceToDest);
      }

      if (BltInfo->PatternSurface)
      {
        Pattern = DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY);
      }

      DIB_4BPP_PutPixel(BltInfo->DestSurface, DestX, DestY, DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern) & 0xF);

      DestX++;
      SourceX++;
      DestBits = (PULONG)((ULONG_PTR)DestBits + 1);
    }

    for (; DestX < RoundedRight; DestX += 8, SourceX += 8, DestBits++)
    {
      Dest = *DestBits;
      if (UsesSource)
      {
        Source =
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 1, SourceY, BltInfo->XlateSourceToDest)) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 0, SourceY, BltInfo->XlateSourceToDest) << 4) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 3, SourceY, BltInfo->XlateSourceToDest) << 8) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 2, SourceY, BltInfo->XlateSourceToDest) << 12) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 5, SourceY, BltInfo->XlateSourceToDest) << 16) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 4, SourceY, BltInfo->XlateSourceToDest) << 20) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 7, SourceY, BltInfo->XlateSourceToDest) << 24) |
          (DIB_GetSource(BltInfo->SourceSurface, SourceX + 6, SourceY, BltInfo->XlateSourceToDest) << 28);
      }
      if (BltInfo->PatternSurface)
      {
        Pattern = DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 1) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY);
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 0) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 4;
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 3) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 8;
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 2) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 12;
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 5) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 16;
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 4) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 20;
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 7) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 24;
        Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x + 6) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY) << 28;
      }
      *DestBits = DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern);
    }

    /* Process the rest of pixel on the line */
    for (; DestX < BltInfo->DestRect.right; DestX++, SourceX++)
    {
      Dest = DIB_4BPP_GetPixel(BltInfo->DestSurface, DestX, DestY);
      if (UsesSource)
      {
        Source = DIB_GetSource(BltInfo->SourceSurface, SourceX, SourceY, BltInfo->XlateSourceToDest);
      }
      if (BltInfo->PatternSurface)
      {
        Pattern = DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX + BltInfo->BrushOrigin.x) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY);
      }
      DIB_4BPP_PutPixel(BltInfo->DestSurface, DestX, DestY, DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern) & 0xF);
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