#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLATEOBJ ;
typedef  int ULONG ;
struct TYPE_23__ {scalar_t__ (* DIB_GetPixel ) (TYPE_2__*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* DIB_PutPixel ) (TYPE_2__*,scalar_t__,scalar_t__,int) ;} ;
struct TYPE_22__ {int iSolidColor; } ;
struct TYPE_21__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_20__ {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
struct TYPE_18__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_19__ {size_t iBitmapFormat; TYPE_1__ sizlBitmap; } ;
typedef  TYPE_2__ SURFOBJ ;
typedef  int ROP4 ;
typedef  TYPE_3__ RECTL ;
typedef  TYPE_4__ POINTL ;
typedef  int /*<<< orphan*/  (* PFN_DIB_PutPixel ) (TYPE_2__*,scalar_t__,scalar_t__,int) ;
typedef  scalar_t__ (* PFN_DIB_GetPixel ) (TYPE_2__*,scalar_t__,scalar_t__) ;
typedef  scalar_t__ LONG ;
typedef  TYPE_7__ BRUSHOBJ ;
typedef  int BOOLEAN ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  BMF_16BPP 132 
#define  BMF_1BPP 131 
#define  BMF_24BPP 130 
#define  BMF_4BPP 129 
#define  BMF_8BPP 128 
 int /*<<< orphan*/  BitsPerFormat (size_t) ; 
 int DIB_DoRop (int,int,int,int) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_8__* DibFunctionsForBitmapFormat ; 
 int FALSE ; 
 int /*<<< orphan*/  IS_VALID_ROP4 (int) ; 
 int R3_OPINDEX_SRCCOPY ; 
 scalar_t__ ROP4_USES_PATTERN (int) ; 
 scalar_t__ ROP4_USES_SOURCE (int) ; 
 int TRUE ; 
 int XLATEOBJ_iXlate (int /*<<< orphan*/ *,scalar_t__) ; 

BOOLEAN DIB_XXBPP_StretchBlt(SURFOBJ *DestSurf, SURFOBJ *SourceSurf, SURFOBJ *MaskSurf,
                            SURFOBJ *PatternSurface,
                            RECTL *DestRect, RECTL *SourceRect,
                            POINTL *MaskOrigin, BRUSHOBJ *Brush,
                            POINTL *BrushOrigin, XLATEOBJ *ColorTranslation,
                            ROP4 ROP)
{
  LONG sx = 0;
  LONG sy = 0;
  LONG DesX;
  LONG DesY;

  LONG DstHeight;
  LONG DstWidth;
  LONG SrcHeight;
  LONG SrcWidth;
  LONG MaskCy;
  LONG SourceCy;

  ULONG Color;
  ULONG Dest, Source = 0, Pattern = 0;
  ULONG xxBPPMask;
  BOOLEAN CanDraw;

  PFN_DIB_GetPixel fnSource_GetPixel = NULL;
  PFN_DIB_GetPixel fnDest_GetPixel = NULL;
  PFN_DIB_PutPixel fnDest_PutPixel = NULL;
  PFN_DIB_GetPixel fnPattern_GetPixel = NULL;
  PFN_DIB_GetPixel fnMask_GetPixel = NULL;

  LONG PatternX = 0, PatternY = 0;

  BOOL UsesSource = ROP4_USES_SOURCE(ROP);
  BOOL UsesPattern = ROP4_USES_PATTERN(ROP);

  ASSERT(IS_VALID_ROP4(ROP));

  fnDest_GetPixel = DibFunctionsForBitmapFormat[DestSurf->iBitmapFormat].DIB_GetPixel;
  fnDest_PutPixel = DibFunctionsForBitmapFormat[DestSurf->iBitmapFormat].DIB_PutPixel;

  DPRINT("Dest BPP: %u, dstRect: (%d,%d)-(%d,%d)\n",
    BitsPerFormat(DestSurf->iBitmapFormat), DestRect->left, DestRect->top, DestRect->right, DestRect->bottom);

  if (UsesSource)
  {
    SourceCy = SourceSurf->sizlBitmap.cy;
    fnSource_GetPixel = DibFunctionsForBitmapFormat[SourceSurf->iBitmapFormat].DIB_GetPixel;
    DPRINT("Source BPP: %u, srcRect: (%d,%d)-(%d,%d)\n",
      BitsPerFormat(SourceSurf->iBitmapFormat), SourceRect->left, SourceRect->top, SourceRect->right, SourceRect->bottom);
  }

  if (MaskSurf)
  {
    fnMask_GetPixel = DibFunctionsForBitmapFormat[MaskSurf->iBitmapFormat].DIB_GetPixel;
    MaskCy = MaskSurf->sizlBitmap.cy;
  }

  DstHeight = DestRect->bottom - DestRect->top;
  DstWidth = DestRect->right - DestRect->left;
  SrcHeight = SourceRect->bottom - SourceRect->top;
  SrcWidth = SourceRect->right - SourceRect->left;

  /* FIXME: MaskOrigin? */

  switch(DestSurf->iBitmapFormat)
  {
  case BMF_1BPP: xxBPPMask = 0x1; break;
  case BMF_4BPP: xxBPPMask = 0xF; break;
  case BMF_8BPP: xxBPPMask = 0xFF; break;
  case BMF_16BPP: xxBPPMask = 0xFFFF; break;
  case BMF_24BPP: xxBPPMask = 0xFFFFFF; break;
  default:
    xxBPPMask = 0xFFFFFFFF;
  }

  if (UsesPattern)
  {
    if (PatternSurface)
    {
      PatternY = (DestRect->top - BrushOrigin->y) % PatternSurface->sizlBitmap.cy;
      if (PatternY < 0)
      {
        PatternY += PatternSurface->sizlBitmap.cy;
      }
      fnPattern_GetPixel = DibFunctionsForBitmapFormat[PatternSurface->iBitmapFormat].DIB_GetPixel;
    }
    else
    {
      if (Brush)
        Pattern = Brush->iSolidColor;
    }
  }


  for (DesY = DestRect->top; DesY < DestRect->bottom; DesY++)
  {
    if (PatternSurface)
    {
      PatternX = (DestRect->left - BrushOrigin->x) % PatternSurface->sizlBitmap.cx;
      if (PatternX < 0)
      {
        PatternX += PatternSurface->sizlBitmap.cx;
      }
    }
    if (UsesSource)
      sy = SourceRect->top+(DesY - DestRect->top) * SrcHeight / DstHeight;

    for (DesX = DestRect->left; DesX < DestRect->right; DesX++)
    {
      CanDraw = TRUE;

      if (fnMask_GetPixel)
      {
        sx = SourceRect->left+(DesX - DestRect->left) * SrcWidth / DstWidth;
        if (sx < 0 || sy < 0 ||
          MaskSurf->sizlBitmap.cx < sx || MaskCy < sy ||
          fnMask_GetPixel(MaskSurf, sx, sy) != 0)
        {
          CanDraw = FALSE;
        }
      }

      if (UsesSource && CanDraw)
      {
        sx = SourceRect->left+(DesX - DestRect->left) * SrcWidth / DstWidth;
        if (sx >= 0 && sy >= 0 &&
          SourceSurf->sizlBitmap.cx > sx && SourceCy > sy)
        {
          Source = XLATEOBJ_iXlate(ColorTranslation, fnSource_GetPixel(SourceSurf, sx, sy));
        }
        else
        {
          Source = 0;
          CanDraw = ((ROP & 0xFF) != R3_OPINDEX_SRCCOPY);
        }
      }

      if (CanDraw)
      {
        if (UsesPattern && PatternSurface)
        {
          Pattern = fnPattern_GetPixel(PatternSurface, PatternX, PatternY);
          PatternX++;
          PatternX %= PatternSurface->sizlBitmap.cx;
        }

        Dest = fnDest_GetPixel(DestSurf, DesX, DesY);
        Color = DIB_DoRop(ROP, Dest, Source, Pattern) & xxBPPMask;

        fnDest_PutPixel(DestSurf, DesX, DesY, Color);
      }
    }

    if (PatternSurface)
    {
      PatternY++;
      PatternY %= PatternSurface->sizlBitmap.cy;
    }
  }

  return TRUE;
}