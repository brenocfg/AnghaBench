#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_14__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
struct TYPE_13__ {int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_12__ {int iBitmapFormat; } ;
struct TYPE_11__ {TYPE_2__* SourceSurface; int /*<<< orphan*/  DestSurface; int /*<<< orphan*/  XlateSourceToDest; TYPE_7__ DestRect; TYPE_8__ SourcePoint; } ;
typedef  TYPE_1__* PBLTINFO ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
#define  BMF_16BPP 133 
#define  BMF_1BPP 132 
#define  BMF_24BPP 131 
#define  BMF_32BPP 130 
#define  BMF_4BPP 129 
#define  BMF_8BPP 128 
 int /*<<< orphan*/  BitsPerFormat (int) ; 
 int /*<<< orphan*/  DIB_16BPP_GetPixel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_1BPP_BitBltSrcCopy_From1BPP (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  DIB_1BPP_PutPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_24BPP_GetPixel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_32BPP_GetPixel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_4BPP_GetPixel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_8BPP_GetPixel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLATEOBJ_iXlate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN
DIB_1BPP_BitBltSrcCopy(PBLTINFO BltInfo)
{
  ULONG Color;
  LONG i, j, sx, sy = BltInfo->SourcePoint.y;

  switch ( BltInfo->SourceSurface->iBitmapFormat )
  {
  case BMF_1BPP:
    DIB_1BPP_BitBltSrcCopy_From1BPP ( BltInfo->DestSurface, BltInfo->SourceSurface, BltInfo->XlateSourceToDest, &BltInfo->DestRect, &BltInfo->SourcePoint );
    break;

  case BMF_4BPP:
    for (j=BltInfo->DestRect.top; j<BltInfo->DestRect.bottom; j++)
    {
      sx = BltInfo->SourcePoint.x;
      for (i=BltInfo->DestRect.left; i<BltInfo->DestRect.right; i++)
      {
        Color = XLATEOBJ_iXlate(BltInfo->XlateSourceToDest, DIB_4BPP_GetPixel(BltInfo->SourceSurface, sx, sy));
        DIB_1BPP_PutPixel(BltInfo->DestSurface, i, j, Color);
        sx++;
      }
      sy++;
    }
    break;

  case BMF_8BPP:
    for (j=BltInfo->DestRect.top; j<BltInfo->DestRect.bottom; j++)
    {
      sx = BltInfo->SourcePoint.x;
      for (i=BltInfo->DestRect.left; i<BltInfo->DestRect.right; i++)
      {
        Color = XLATEOBJ_iXlate(BltInfo->XlateSourceToDest, DIB_8BPP_GetPixel(BltInfo->SourceSurface, sx, sy));
        DIB_1BPP_PutPixel(BltInfo->DestSurface, i, j, Color);
        sx++;
      }
      sy++;
    }
    break;

  case BMF_16BPP:
    for (j=BltInfo->DestRect.top; j<BltInfo->DestRect.bottom; j++)
    {
      sx = BltInfo->SourcePoint.x;
      for (i=BltInfo->DestRect.left; i<BltInfo->DestRect.right; i++)
      {
        Color = XLATEOBJ_iXlate(BltInfo->XlateSourceToDest, DIB_16BPP_GetPixel(BltInfo->SourceSurface, sx, sy));
        DIB_1BPP_PutPixel(BltInfo->DestSurface, i, j, Color);
        sx++;
      }
      sy++;
    }
    break;

  case BMF_24BPP:
    for (j=BltInfo->DestRect.top; j<BltInfo->DestRect.bottom; j++)
    {
      sx = BltInfo->SourcePoint.x;
      for (i=BltInfo->DestRect.left; i<BltInfo->DestRect.right; i++)
      {
        Color = XLATEOBJ_iXlate(BltInfo->XlateSourceToDest, DIB_24BPP_GetPixel(BltInfo->SourceSurface, sx, sy));
        DIB_1BPP_PutPixel(BltInfo->DestSurface, i, j, Color);
        sx++;
      }
      sy++;
    }
    break;

  case BMF_32BPP:
    for (j=BltInfo->DestRect.top; j<BltInfo->DestRect.bottom; j++)
    {
      sx = BltInfo->SourcePoint.x;
      for (i=BltInfo->DestRect.left; i<BltInfo->DestRect.right; i++)
      {
        Color = XLATEOBJ_iXlate(BltInfo->XlateSourceToDest, DIB_32BPP_GetPixel(BltInfo->SourceSurface, sx, sy));
        DIB_1BPP_PutPixel(BltInfo->DestSurface, i, j, Color);
        sx++;
      }
      sy++;
    }
    break;

  default:
    DbgPrint("DIB_1BPP_BitBlt: Unhandled Source BPP: %u\n", BitsPerFormat(BltInfo->SourceSurface->iBitmapFormat));
    return FALSE;
  }

  return TRUE;
}