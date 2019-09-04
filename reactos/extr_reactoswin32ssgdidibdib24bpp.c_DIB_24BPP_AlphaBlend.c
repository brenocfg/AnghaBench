#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLATEOBJ ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int UCHAR ;
struct TYPE_18__ {scalar_t__ BlendOp; scalar_t__ BlendFlags; int AlphaFormat; int SourceConstantAlpha; } ;
struct TYPE_17__ {TYPE_6__ BlendFunction; } ;
struct TYPE_13__ {int red; int green; int blue; int alpha; } ;
struct TYPE_16__ {TYPE_1__ col; int /*<<< orphan*/  ul; } ;
struct TYPE_15__ {int left; int top; int right; int bottom; } ;
struct TYPE_14__ {int lDelta; scalar_t__ pvScan0; int /*<<< orphan*/  iBitmapFormat; } ;
typedef  TYPE_2__ SURFOBJ ;
typedef  TYPE_3__ RECTL ;
typedef  int* PUCHAR ;
typedef  TYPE_4__ NICEPIXEL32 ;
typedef  int INT ;
typedef  int /*<<< orphan*/  CLIPOBJ ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_5__ BLENDOBJ ;
typedef  TYPE_6__ BLENDFUNCTION ;

/* Variables and functions */
 int AC_SRC_ALPHA ; 
 scalar_t__ AC_SRC_OVER ; 
 int BitsPerFormat (int /*<<< orphan*/ ) ; 
 void* Clamp8 (int) ; 
 int /*<<< orphan*/  DIB_GetSource (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
DIB_24BPP_AlphaBlend(SURFOBJ* Dest, SURFOBJ* Source, RECTL* DestRect,
                     RECTL* SourceRect, CLIPOBJ* ClipRegion,
                     XLATEOBJ* ColorTranslation, BLENDOBJ* BlendObj)
{
   INT Rows, Cols, SrcX, SrcY;
   register PUCHAR Dst;
   BLENDFUNCTION BlendFunc;
   register NICEPIXEL32 DstPixel, SrcPixel;
   UCHAR Alpha;
   //UCHAR SrcBpp;

   DPRINT("DIB_24BPP_AlphaBlend: srcRect: (%d,%d)-(%d,%d), dstRect: (%d,%d)-(%d,%d)\n",
          SourceRect->left, SourceRect->top, SourceRect->right, SourceRect->bottom,
          DestRect->left, DestRect->top, DestRect->right, DestRect->bottom);

   BlendFunc = BlendObj->BlendFunction;
   if (BlendFunc.BlendOp != AC_SRC_OVER)
   {
      DPRINT1("BlendOp != AC_SRC_OVER\n");
      return FALSE;
   }
   if (BlendFunc.BlendFlags != 0)
   {
      DPRINT1("BlendFlags != 0\n");
      return FALSE;
   }
   if ((BlendFunc.AlphaFormat & ~AC_SRC_ALPHA) != 0)
   {
      DPRINT1("Unsupported AlphaFormat (0x%x)\n", BlendFunc.AlphaFormat);
      return FALSE;
   }
   if ((BlendFunc.AlphaFormat & AC_SRC_ALPHA) != 0 &&
       BitsPerFormat(Source->iBitmapFormat) != 32)
   {
      DPRINT1("Source bitmap must be 32bpp when AC_SRC_ALPHA is set\n");
      return FALSE;
   }

   Dst = (PUCHAR)((ULONG_PTR)Dest->pvScan0 + (DestRect->top * Dest->lDelta) +
                             (DestRect->left * 3));
   //SrcBpp = BitsPerFormat(Source->iBitmapFormat);

   Rows = 0;
   SrcY = SourceRect->top;
   while (++Rows <= DestRect->bottom - DestRect->top)
  {
    Cols = 0;
    SrcX = SourceRect->left;
    while (++Cols <= DestRect->right - DestRect->left)
    {
      SrcPixel.ul = DIB_GetSource(Source, SrcX, SrcY, ColorTranslation);
      SrcPixel.col.red = (SrcPixel.col.red * BlendFunc.SourceConstantAlpha) / 255;
      SrcPixel.col.green = (SrcPixel.col.green * BlendFunc.SourceConstantAlpha) / 255;
      SrcPixel.col.blue = (SrcPixel.col.blue * BlendFunc.SourceConstantAlpha) / 255;
      if (!(BlendFunc.AlphaFormat & AC_SRC_ALPHA))
      {
          Alpha = BlendFunc.SourceConstantAlpha ;
      }
      else
      {
        Alpha = (SrcPixel.col.alpha * BlendFunc.SourceConstantAlpha) / 255;
      }

      DstPixel.col.red = Clamp8((*Dst * (255 - Alpha)) / 255 + SrcPixel.col.red) ;
      DstPixel.col.green = Clamp8((*(Dst+1) * (255 - Alpha) / 255 + SrcPixel.col.green)) ;
      DstPixel.col.blue = Clamp8((*(Dst+2) * (255 - Alpha)) / 255 + SrcPixel.col.blue) ;
      *Dst++ = DstPixel.col.red;
      *Dst++ = DstPixel.col.green;
      *Dst++ = DstPixel.col.blue;
      SrcX = SourceRect->left + (Cols*(SourceRect->right - SourceRect->left))/(DestRect->right - DestRect->left);
    }
    Dst = (PUCHAR)((ULONG_PTR)Dest->pvScan0 + ((DestRect->top + Rows) * Dest->lDelta) +
                (DestRect->left*3));
    SrcY = SourceRect->top + (Rows*(SourceRect->bottom - SourceRect->top))/(DestRect->bottom - DestRect->top);
  }

   return TRUE;
}