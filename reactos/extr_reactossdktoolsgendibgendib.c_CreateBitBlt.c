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
 int /*<<< orphan*/  MARK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
CreateBitBlt(FILE *Out, unsigned Bpp)
{
    MARK(Out);
    Output(Out, "\n");
    Output(Out, "BOOLEAN\n");
    Output(Out, "DIB_%uBPP_BitBlt(PBLTINFO BltInfo)\n", Bpp);
    Output(Out, "{\n");
    Output(Out, "PrimitivesTable[BltInfo->Rop4 & 0xff](BltInfo);\n");
    Output(Out, "\n");
    Output(Out, "return TRUE;\n");
    Output(Out, "}\n");
}