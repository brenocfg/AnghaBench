#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ RopCode; scalar_t__ UsesSource; scalar_t__ UsesPattern; } ;
typedef  TYPE_1__* PROPINFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBase (int /*<<< orphan*/ *,int,int,unsigned int) ; 
 int /*<<< orphan*/  CreateCounts (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  CreateGetSource (int /*<<< orphan*/ *,unsigned int,TYPE_1__*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  CreateOperation (int /*<<< orphan*/ *,unsigned int,TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  CreateSetSinglePixel (int /*<<< orphan*/ *,unsigned int,TYPE_1__*,int,unsigned int) ; 
 int FLAG_BOTTOMUP ; 
 int FLAG_FORCENOUSESSOURCE ; 
 int FLAG_FORCERAWSOURCEAVAIL ; 
 int FLAG_PATTERNSURFACE ; 
 int FLAG_TRIVIALXLATE ; 
 int /*<<< orphan*/  MARK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ROPCODE_SRCCOPY ; 

__attribute__((used)) static void
CreateBitCase(FILE *Out, unsigned Bpp, PROPINFO RopInfo, int Flags,
              unsigned SourceBpp)
{
    unsigned Partial;

    MARK(Out);
    if (RopInfo->UsesSource)
    {
        if (0 == (Flags & FLAG_FORCENOUSESSOURCE))
        {
            CreateBase(Out, 1, Flags, SourceBpp);
        }
        CreateBase(Out, 0, Flags, Bpp);
        CreateCounts(Out, Bpp);
        MARK(Out);
    }
    if (RopInfo->UsesPattern && 0 != (Flags & FLAG_PATTERNSURFACE))
    {
        if (0 == (Flags & FLAG_BOTTOMUP))
        {
            Output(Out, "PatternY = (BltInfo->DestRect.top - BltInfo->BrushOrigin.y) %%\n");
            Output(Out, "           BltInfo->PatternSurface->sizlBitmap.cy;\n");
        }
        else
        {
            Output(Out, "PatternY = (BltInfo->DestRect.bottom - 1 -\n");
            Output(Out, "            BltInfo->BrushOrigin.y) %%\n");
            Output(Out, "           BltInfo->PatternSurface->sizlBitmap.cy;\n");
        }
    }
    if (ROPCODE_SRCCOPY == RopInfo->RopCode &&
            0 != (Flags & FLAG_TRIVIALXLATE) && Bpp == SourceBpp)
    {
        Output(Out, "CenterCount = %u * (BltInfo->DestRect.right -\n", Bpp >> 3);
        Output(Out, "                   BltInfo->DestRect.left);\n");
    }
    if (RopInfo->UsesPattern && 0 != (Flags & FLAG_PATTERNSURFACE))
    {
        Output(Out, "BasePatternX = (BltInfo->DestRect.left - BltInfo->BrushOrigin.x) %%\n");
        Output(Out, "           BltInfo->PatternSurface->sizlBitmap.cx;\n");
    }

    Output(Out, "for (LineIndex = 0; LineIndex < LineCount; LineIndex++)\n");
    Output(Out, "{\n");
    if (ROPCODE_SRCCOPY != RopInfo->RopCode ||
            0 == (Flags & FLAG_TRIVIALXLATE) || Bpp != SourceBpp)
    {
        if (RopInfo->UsesSource && 0 == (Flags & FLAG_FORCENOUSESSOURCE))
        {
            Output(Out, "SourcePtr = (PULONG) SourceBase;\n");
            if (SourceBpp <= 16)
            {
                Output(Out, "RawSource = *SourcePtr++;\n");
                Output(Out, "SourcePixels = BaseSourcePixels;\n");
            }
        }
        Output(Out, "DestPtr = (PULONG) DestBase;\n");
    }

    if (RopInfo->UsesPattern && 0 != (Flags & FLAG_PATTERNSURFACE))
    {
        Output(Out, "PatternX = BasePatternX;\n");
    }

    if (ROPCODE_SRCCOPY == RopInfo->RopCode &&
            0 != (Flags & FLAG_TRIVIALXLATE) && Bpp == SourceBpp)
    {
        Output(Out, "RtlMoveMemory(DestBase, SourceBase, CenterCount);\n");
        Output(Out, "\n");
    }
    else
    {
        Output(Out, "\n");
        if (32 != Bpp)
        {
            if (16 == Bpp)
            {
                Output(Out, "if (0 != LeftCount)\n");
            }
            else
            {
                Output(Out, "for (i = 0; i < LeftCount; i++)\n");
            }
            Output(Out, "{\n");
            CreateSetSinglePixel(Out, Bpp, RopInfo,
                                 (16 == Bpp ? Flags | FLAG_FORCERAWSOURCEAVAIL :
                                  Flags), SourceBpp);
            MARK(Out);
            Output(Out, "}\n");
            Output(Out, "\n");
        }
        Output(Out, "for (i = 0; i < CenterCount; i++)\n");
        Output(Out, "{\n");
        if (RopInfo->UsesSource && 0 == (Flags & FLAG_FORCENOUSESSOURCE))
        {
            for (Partial = 0; Partial < 32 / Bpp; Partial++)
            {
                CreateGetSource(Out, Bpp, RopInfo, Flags, SourceBpp,
                                Partial * Bpp);
                MARK(Out);
            }
            Output(Out, "\n");
        }
        if (RopInfo->UsesPattern && 0 != (Flags & FLAG_PATTERNSURFACE))
        {
            for (Partial = 0; Partial < 32 / Bpp; Partial++)
            {
                if (0 == Partial)
                {
                    Output(Out, "Pattern = DIB_GetSourceIndex(BltInfo->PatternSurface, PatternX, PatternY);\n");
                }
                else
                {
                    Output(Out, "Pattern |= DIB_GetSourceIndex(BltInfo->PatternSurface, PatternX, PatternY) << %u;\n", Partial * Bpp);
                }
                Output(Out, "if (BltInfo->PatternSurface->sizlBitmap.cx <= ++PatternX)\n");
                Output(Out, "{\n");
                Output(Out, "PatternX -= BltInfo->PatternSurface->sizlBitmap.cx;\n");
                Output(Out, "}\n");
            }
            Output(Out, "\n");
        }
        CreateOperation(Out, Bpp, RopInfo, SourceBpp, 32);
        Output(Out, ";\n");
        MARK(Out);
        Output(Out, "\n");
        Output(Out, "DestPtr++;\n");
        Output(Out, "}\n");
        Output(Out, "\n");
        if (32 != Bpp)
        {
            if (16 == Bpp)
            {
                Output(Out, "if (0 != RightCount)\n");
            }
            else
            {
                Output(Out, "for (i = 0; i < RightCount; i++)\n");
            }
            Output(Out, "{\n");
            CreateSetSinglePixel(Out, Bpp, RopInfo, Flags, SourceBpp);
            MARK(Out);
            Output(Out, "}\n");
            Output(Out, "\n");
        }
        if (RopInfo->UsesPattern && 0 != (Flags & FLAG_PATTERNSURFACE))
        {
            if (0 == (Flags & FLAG_BOTTOMUP))
            {
                Output(Out, "if (BltInfo->PatternSurface->sizlBitmap.cy <= ++PatternY)\n");
                Output(Out, "{\n");
                Output(Out, "PatternY -= BltInfo->PatternSurface->sizlBitmap.cy;\n");
                Output(Out, "}\n");
            }
            else
            {
                Output(Out, "if (0 == PatternY--)\n");
                Output(Out, "{\n");
                Output(Out, "PatternY = BltInfo->PatternSurface->sizlBitmap.cy - 1;\n");
                Output(Out, "}\n");
            }
        }
    }
    if (RopInfo->UsesSource && 0 == (Flags & FLAG_FORCENOUSESSOURCE))
    {
        Output(Out, "SourceBase %c= BltInfo->SourceSurface->lDelta;\n",
               0 == (Flags & FLAG_BOTTOMUP) ? '+' : '-');
    }
    Output(Out, "DestBase %c= BltInfo->DestSurface->lDelta;\n",
           0 == (Flags & FLAG_BOTTOMUP) ? '+' : '-');
    Output(Out, "}\n");
}