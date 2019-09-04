#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLATEOBJ ;
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_11__ {int bottom; int top; int right; int left; } ;
struct TYPE_9__ {int cx; int cy; } ;
struct TYPE_10__ {int lDelta; TYPE_1__ sizlBitmap; scalar_t__ pvScan0; } ;
typedef  TYPE_2__ SURFOBJ ;
typedef  TYPE_3__ RECTL ;
typedef  scalar_t__* PULONG ;
typedef  scalar_t__ PBYTE ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ DIB_GetSourceIndex (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int XLATEOBJ_iXlate (int /*<<< orphan*/ *,scalar_t__) ; 

BOOLEAN
DIB_16BPP_TransparentBlt(SURFOBJ *DestSurf, SURFOBJ *SourceSurf,
                         RECTL*  DestRect,  RECTL *SourceRect,
                         XLATEOBJ *ColorTranslation, ULONG iTransColor)
{
  LONG RoundedRight, X, Y, SourceX = 0, SourceY = 0, wd;
  ULONG *DestBits, Source, Dest;

  LONG DstHeight;
  LONG DstWidth;
  LONG SrcHeight;
  LONG SrcWidth;

  DstHeight = DestRect->bottom - DestRect->top;
  DstWidth = DestRect->right - DestRect->left;
  SrcHeight = SourceRect->bottom - SourceRect->top;
  SrcWidth = SourceRect->right - SourceRect->left;

  RoundedRight = DestRect->right - ((DestRect->right - DestRect->left) & 0x1);
  DestBits = (ULONG*)((PBYTE)DestSurf->pvScan0 +
    (DestRect->left << 1) +
    DestRect->top * DestSurf->lDelta);
  wd = DestSurf->lDelta - ((DestRect->right - DestRect->left) << 1);

  for(Y = DestRect->top; Y < DestRect->bottom; Y++)
  {
    SourceY = SourceRect->top+(Y - DestRect->top) * SrcHeight / DstHeight;
    for(X = DestRect->left; X < RoundedRight; X += 2, DestBits++, SourceX += 2)
    {
      Dest = *DestBits;

      SourceX = SourceRect->left+(X - DestRect->left) * SrcWidth / DstWidth;
      if (SourceX >= 0 && SourceY >= 0 &&
        SourceSurf->sizlBitmap.cx > SourceX && SourceSurf->sizlBitmap.cy > SourceY)
      {
        Source = DIB_GetSourceIndex(SourceSurf, SourceX, SourceY);
        if(Source != iTransColor)
        {
          Dest &= 0xFFFF0000;
          Dest |= (XLATEOBJ_iXlate(ColorTranslation, Source) & 0xFFFF);
        }
      }

      SourceX = SourceRect->left+(X+1 - DestRect->left) * SrcWidth / DstWidth;
      if (SourceX >= 0 && SourceY >= 0 &&
        SourceSurf->sizlBitmap.cx > SourceX && SourceSurf->sizlBitmap.cy > SourceY)
      {
        Source = DIB_GetSourceIndex(SourceSurf, SourceX, SourceY);
        if(Source != iTransColor)
        {
          Dest &= 0xFFFF;
          Dest |= (XLATEOBJ_iXlate(ColorTranslation, Source) << 16);
        }
      }

      *DestBits = Dest;
    }

    if(X < DestRect->right)
    {
      SourceX = SourceRect->left+(X - DestRect->left) * SrcWidth / DstWidth;
      if (SourceX >= 0 && SourceY >= 0 &&
        SourceSurf->sizlBitmap.cx > SourceX && SourceSurf->sizlBitmap.cy > SourceY)
      {
        Source = DIB_GetSourceIndex(SourceSurf, SourceX, SourceY);
        if(Source != iTransColor)
        {
          *((USHORT*)DestBits) = (USHORT)XLATEOBJ_iXlate(ColorTranslation,
            Source);
        }
      }

      DestBits = (PULONG)((ULONG_PTR)DestBits + 2);
    }

    DestBits = (ULONG*)((ULONG_PTR)DestBits + wd);
  }

  return TRUE;
}