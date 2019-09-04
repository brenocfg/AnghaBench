#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FindRopInfo (unsigned int) ; 
 int /*<<< orphan*/  MARK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PrintRoutineName (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CreateTable(FILE *Out, unsigned Bpp)
{
    unsigned RopCode;

    MARK(Out);
    Output(Out, "\n");
    Output(Out, "static void (*PrimitivesTable[256])(PBLTINFO) =\n");
    Output(Out, "{\n");
    for (RopCode = 0; RopCode < 256; RopCode++)
    {
        PrintRoutineName(Out, Bpp, FindRopInfo(RopCode));
        if (RopCode < 255)
        {
            Output(Out, ",");
        }
        Output(Out, "\n");
    }
    Output(Out, "};\n");
}