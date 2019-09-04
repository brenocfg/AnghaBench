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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_11__ {scalar_t__ bottom; scalar_t__ top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_9__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_10__ {int lDelta; TYPE_1__ sizlBitmap; scalar_t__ pvScan0; } ;
typedef  TYPE_2__ SURFOBJ ;
typedef  TYPE_3__ RECTL ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int DIB_GetSourceIndex (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int XLATEOBJ_iXlate (int /*<<< orphan*/ *,int) ; 

BOOLEAN
DIB_32BPP_TransparentBlt(SURFOBJ *DestSurf, SURFOBJ *SourceSurf,
                         RECTL*  DestRect,  RECTL *SourceRect,
                         XLATEOBJ *ColorTranslation, ULONG iTransColor)
{
  LONG X, Y, SourceX, SourceY = 0, wd;
  ULONG *DestBits, Source = 0;

  LONG DstHeight;
  LONG DstWidth;
  LONG SrcHeight;
  LONG SrcWidth;

  DstHeight = DestRect->bottom - DestRect->top;
  DstWidth = DestRect->right - DestRect->left;
  SrcHeight = SourceRect->bottom - SourceRect->top;
  SrcWidth = SourceRect->right - SourceRect->left;

  DestBits = (ULONG*)((PBYTE)DestSurf->pvScan0 +
    (DestRect->left << 2) +
    DestRect->top * DestSurf->lDelta);
  wd = DestSurf->lDelta - ((DestRect->right - DestRect->left) << 2);

  for (Y = DestRect->top; Y < DestRect->bottom; Y++)
  {
    SourceY = SourceRect->top+(Y - DestRect->top) * SrcHeight / DstHeight;
    for (X = DestRect->left; X < DestRect->right; X++, DestBits++)
    {
      SourceX = SourceRect->left+(X - DestRect->left) * SrcWidth / DstWidth;
      if (SourceX >= 0 && SourceY >= 0 &&
        SourceSurf->sizlBitmap.cx > SourceX && SourceSurf->sizlBitmap.cy > SourceY)
      {
        Source = DIB_GetSourceIndex(SourceSurf, SourceX, SourceY);
        if ((0x00FFFFFF & Source) != (0x00FFFFFF & iTransColor))
        {
          *DestBits = XLATEOBJ_iXlate(ColorTranslation, Source);
        }
      }
    }

    DestBits = (ULONG*)((ULONG_PTR)DestBits + wd);
  }

  return TRUE;
}