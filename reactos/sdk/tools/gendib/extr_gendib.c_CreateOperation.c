#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ RopCode; char* Operation; } ;
typedef  TYPE_1__* PROPINFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MARK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Output (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ROPCODE_GENERIC ; 

__attribute__((used)) static void
CreateOperation(FILE *Out, unsigned Bpp, PROPINFO RopInfo, unsigned SourceBpp,
                unsigned Bits)
{
    const char *Cast;
    const char *Dest;
    const char *Template;

    MARK(Out);
    if (32 == Bits)
    {
        Cast = "";
        Dest = "*DestPtr";
    }
    else if (16 == Bpp)
    {
        Cast = "(USHORT) ";
        Dest = "*((PUSHORT) DestPtr)";
    }
    else
    {
        Cast = "(UCHAR) ";
        Dest = "*((PUCHAR) DestPtr)";
    }
    Output(Out, "%s = ", Dest);
    if (ROPCODE_GENERIC == RopInfo->RopCode)
    {
        Output(Out, "%sDIB_DoRop(BltInfo->Rop4, %s, Source, Pattern)",
               Cast, Dest);
    }
    else
    {
        Template = RopInfo->Operation;
        while ('\0' != *Template)
        {
            switch(*Template)
            {
            case 'S':
                Output(Out, "%sSource", Cast);
                break;
            case 'P':
                Output(Out, "%sPattern", Cast);
                break;
            case 'D':
                Output(Out, "%s", Dest);
                break;
            default:
                Output(Out, "%c", *Template);
                break;
            }
            Template++;
        }
    }
}