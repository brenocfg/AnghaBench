#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ RopCode; scalar_t__ UsesPattern; scalar_t__ UsesSource; } ;
typedef  TYPE_1__* PROPINFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateActionBlock (int /*<<< orphan*/ *,unsigned int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBase (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  CreateCounts (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  FLAG_PATTERNSURFACE ; 
 int /*<<< orphan*/  MARK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  PrintRoutineName (int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ; 
 scalar_t__ ROPCODE_BLACKNESS ; 
 scalar_t__ ROPCODE_GENERIC ; 
 scalar_t__ ROPCODE_MERGECOPY ; 
 scalar_t__ ROPCODE_NOOP ; 
 scalar_t__ ROPCODE_PATINVERT ; 
 scalar_t__ ROPCODE_PATPAINT ; 
 scalar_t__ ROPCODE_WHITENESS ; 

__attribute__((used)) static void
CreatePrimitive(FILE *Out, unsigned Bpp, PROPINFO RopInfo)
{
    int First;
    unsigned Partial;

    MARK(Out);
    Output(Out, "\n");
    Output(Out, "static void\n");
    PrintRoutineName(Out, Bpp, RopInfo);
    Output(Out, "(PBLTINFO BltInfo)\n");
    Output(Out, "{\n");
    if (ROPCODE_BLACKNESS == RopInfo->RopCode)
    {
        Output(Out, "DIB_%uBPP_ColorFill(BltInfo->DestSurface, "
               "&BltInfo->DestRect, 0x0);\n", Bpp);
    }
    else if (ROPCODE_WHITENESS == RopInfo->RopCode)
    {
        Output(Out, "DIB_%uBPP_ColorFill(BltInfo->DestSurface, "
               "&BltInfo->DestRect, ~0);\n", Bpp);
    }
    else if (ROPCODE_NOOP == RopInfo->RopCode)
    {
        Output(Out, "return;\n");
    }
    else
    {
        Output(Out, "ULONG LineIndex, LineCount;\n");
        Output(Out, "ULONG i;\n");
        if (RopInfo->UsesPattern)
        {
            Output(Out, "LONG PatternX =0, PatternY = 0, BasePatternX = 0;\n");
        }
        First = 1;
        if (RopInfo->UsesSource)
        {
            Output(Out, "ULONG Source = 0");
            First = 0;
        }
        if (RopInfo->UsesPattern)
        {
            Output(Out, "%s Pattern = 0", First ? "ULONG" : ",");
            First = 0;
        }
        if (! First)
        {
            Output(Out, ";\n");
        }
        Output(Out, "char *DestBase;\n");
        Output(Out, "PULONG DestPtr;\n");
        if (RopInfo->UsesSource)
        {
            Output(Out, "char *SourceBase;\n");
            Output(Out, "PULONG SourcePtr;\n");
            Output(Out, "ULONG RawSource;\n");
            Output(Out, "unsigned SourcePixels, BaseSourcePixels;\n");
        }
        if (32 == Bpp)
        {
            Output(Out, "ULONG CenterCount;\n");
        }
        else
        {
            Output(Out, "ULONG LeftCount, CenterCount, RightCount;\n");
        }
        if (ROPCODE_GENERIC == RopInfo->RopCode)
        {
            Output(Out, "BOOLEAN UsesSource, UsesPattern;\n");
            Output(Out, "\n");
            Output(Out, "UsesSource = ROP4_USES_SOURCE(BltInfo->Rop4);\n");
            Output(Out, "UsesPattern = ROP4_USES_PATTERN(BltInfo->Rop4);\n");
        }
        Output(Out, "\n");
        if (! RopInfo->UsesSource)
        {
            CreateBase(Out, 0, 0, Bpp);
            CreateCounts(Out, Bpp);
            MARK(Out);
        }
        Output(Out, "LineCount = BltInfo->DestRect.bottom - BltInfo->DestRect.top;\n");

        Output(Out, "\n");
        if (RopInfo->UsesPattern)
        {
            if (ROPCODE_GENERIC == RopInfo->RopCode)
            {
                Output(Out, "if (UsesPattern && NULL != BltInfo->PatternSurface)\n");
            }
            else
            {
                Output(Out, "if (NULL != BltInfo->PatternSurface)\n");
            }
            Output(Out, "{\n");
            CreateActionBlock(Out, Bpp, RopInfo, FLAG_PATTERNSURFACE);
            MARK(Out);
            Output(Out, "}\n");
            Output(Out, "else\n");
            Output(Out, "{\n");
            if (ROPCODE_GENERIC == RopInfo->RopCode)
            {
                Output(Out, "if (UsesPattern)\n");
                Output(Out, "{\n");
            }
            for (Partial = 0; Partial < 32 / Bpp; Partial++)
            {
                if (0 == Partial)
                {
                    Output(Out, "if (!BltInfo->Brush)\n");
                    Output(Out, "{\n");
                    Output(Out, "Pattern = 0;\n");
                    Output(Out, "}\n");
                    Output(Out, "else\n");
                    Output(Out, "{\n");
                    Output(Out, "Pattern = BltInfo->Brush->iSolidColor");
                }
                else
                {
                    Output(Out, "          (BltInfo->Brush->iSolidColor << %d)",
                           Partial * Bpp);
                }
                if (32 / Bpp <= Partial + 1)
                {
                    Output(Out, ";\n");
                    Output(Out, "}\n");
                }
                else
                {
                    Output(Out, " |\n");
                }
            }
            if (ROPCODE_PATINVERT == RopInfo->RopCode ||
                    ROPCODE_MERGECOPY == RopInfo->RopCode)
            {
                Output(Out, "if (0 == Pattern)\n");
                Output(Out, "{\n");
                if (ROPCODE_MERGECOPY == RopInfo->RopCode)
                {
                    Output(Out, "DIB_%uBPP_ColorFill(BltInfo->DestSurface, "
                           "&BltInfo->DestRect, 0x0);\n", Bpp);
                }
                Output(Out, "return;\n");
                Output(Out, "}\n");
            }
            else if (ROPCODE_PATPAINT == RopInfo->RopCode)
            {
                Output(Out, "if ((~0) == Pattern)\n");
                Output(Out, "{\n");
                Output(Out, "DIB_%uBPP_ColorFill(BltInfo->DestSurface, "
                       "&BltInfo->DestRect, ~0);\n", Bpp);
                Output(Out, "return;\n");
                Output(Out, "}\n");
            }
            if (ROPCODE_GENERIC == RopInfo->RopCode)
            {
                Output(Out, "}\n");
            }
            CreateActionBlock(Out, Bpp, RopInfo, 0);
            MARK(Out);
            Output(Out, "}\n");
        }
        else
        {
            CreateActionBlock(Out, Bpp, RopInfo, 0);
            MARK(Out);
        }
    }
    Output(Out, "}\n");
}