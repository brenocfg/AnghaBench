#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_13__ {int cy; int cx; } ;
struct TYPE_17__ {TYPE_4__ sizlBitmap; } ;
struct TYPE_14__ {int left; int top; int bottom; int right; } ;
struct TYPE_12__ {int y; int x; } ;
struct TYPE_11__ {int y; int x; } ;
struct TYPE_16__ {TYPE_6__* DestSurface; TYPE_5__ DestRect; TYPE_8__* PatternSurface; int /*<<< orphan*/  Rop4; TYPE_3__ BrushOrigin; int /*<<< orphan*/  XlateSourceToDest; int /*<<< orphan*/  SourceSurface; TYPE_2__ SourcePoint; TYPE_1__* Brush; } ;
struct TYPE_15__ {int lDelta; scalar_t__ pvScan0; } ;
struct TYPE_10__ {int iSolidColor; } ;
typedef  int* PUSHORT ;
typedef  int* PBYTE ;
typedef  TYPE_7__* PBLTINFO ;
typedef  int LONG ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DIB_DoRop (int /*<<< orphan*/ ,int,int,int) ; 
 int DIB_GetSource (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int DIB_GetSourceIndex (TYPE_8__*,int,int) ; 
 scalar_t__ ROP4_USES_PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ ROP4_USES_SOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
DIB_24BPP_BitBlt(PBLTINFO BltInfo)
{
   LONG DestX, DestY;
   LONG SourceX, SourceY;
   LONG PatternY = 0;
   ULONG Dest, Source = 0, Pattern = 0;
   BOOL UsesSource;
   BOOL UsesPattern;
   PBYTE DestBits;

   UsesSource = ROP4_USES_SOURCE(BltInfo->Rop4);
   UsesPattern = ROP4_USES_PATTERN(BltInfo->Rop4);

   SourceY = BltInfo->SourcePoint.y;
   DestBits = (PBYTE)(
      (PBYTE)BltInfo->DestSurface->pvScan0 +
      (BltInfo->DestRect.left << 1) + BltInfo->DestRect.left +
      BltInfo->DestRect.top * BltInfo->DestSurface->lDelta);

   if (UsesPattern)
   {
      if (BltInfo->PatternSurface)
      {
         PatternY = (BltInfo->DestRect.top - BltInfo->BrushOrigin.y) %
                    BltInfo->PatternSurface->sizlBitmap.cy;
      }
      else
      {
         if (BltInfo->Brush)
            Pattern = BltInfo->Brush->iSolidColor;
      }
   }

   for (DestY = BltInfo->DestRect.top; DestY < BltInfo->DestRect.bottom; DestY++)
   {
      SourceX = BltInfo->SourcePoint.x;

      for (DestX = BltInfo->DestRect.left; DestX < BltInfo->DestRect.right; DestX++, DestBits += 3, SourceX++)
      {
         Dest = *((PUSHORT)DestBits) + (*(DestBits + 2) << 16);

         if (UsesSource)
         {
            Source = DIB_GetSource(BltInfo->SourceSurface, SourceX, SourceY, BltInfo->XlateSourceToDest);
         }

         if (BltInfo->PatternSurface)
         {
            Pattern = DIB_GetSourceIndex(BltInfo->PatternSurface, (DestX - BltInfo->BrushOrigin.x) % BltInfo->PatternSurface->sizlBitmap.cx, PatternY);
         }

         Dest = DIB_DoRop(BltInfo->Rop4, Dest, Source, Pattern) & 0xFFFFFF;
         *(PUSHORT)(DestBits) = Dest & 0xFFFF;
         *(DestBits + 2) = (BYTE)(Dest >> 16);
      }

      SourceY++;
      if (BltInfo->PatternSurface)
      {
         PatternY++;
         PatternY %= BltInfo->PatternSurface->sizlBitmap.cy;
      }
      DestBits -= (BltInfo->DestRect.right - BltInfo->DestRect.left) * 3;
      DestBits += BltInfo->DestSurface->lDelta;
   }

   return TRUE;
}