#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_2__ {int Limit; int Base; } ;
typedef  int /*<<< orphan*/  SegDesc ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  char* PCHAR ;
typedef  TYPE_1__ KDESCRIPTOR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 int /*<<< orphan*/  KdbpSafeReadMemory (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Ke386GetGlobalDescriptorTable (int*) ; 
 int Ke386GetLocalDescriptorTable () ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __sidt (int*) ; 

__attribute__((used)) static BOOLEAN
KdbpCmdGdtLdtIdt(
    ULONG Argc,
    PCHAR Argv[])
{
    KDESCRIPTOR Reg;
    ULONG SegDesc[2];
    ULONG SegBase;
    ULONG SegLimit;
    PCHAR SegType;
    USHORT SegSel;
    UCHAR Type, Dpl;
    INT i;
    ULONG ul;

    if (Argv[0][0] == 'i')
    {
        /* Read IDTR */
        __sidt(&Reg.Limit);

        if (Reg.Limit < 7)
        {
            KdbpPrint("Interrupt descriptor table is empty.\n");
            return TRUE;
        }

        KdbpPrint("IDT Base: 0x%08x  Limit: 0x%04x\n", Reg.Base, Reg.Limit);
        KdbpPrint("  Idx  Type        Seg. Sel.  Offset      DPL\n");

        for (i = 0; (i + sizeof(SegDesc) - 1) <= Reg.Limit; i += 8)
        {
            if (!NT_SUCCESS(KdbpSafeReadMemory(SegDesc, (PVOID)(Reg.Base + i), sizeof(SegDesc))))
            {
                KdbpPrint("Couldn't access memory at 0x%08x!\n", Reg.Base + i);
                return TRUE;
            }

            Dpl = ((SegDesc[1] >> 13) & 3);
            if ((SegDesc[1] & 0x1f00) == 0x0500)        /* Task gate */
                SegType = "TASKGATE";
            else if ((SegDesc[1] & 0x1fe0) == 0x0e00)   /* 32 bit Interrupt gate */
                SegType = "INTGATE32";
            else if ((SegDesc[1] & 0x1fe0) == 0x0600)   /* 16 bit Interrupt gate */
                SegType = "INTGATE16";
            else if ((SegDesc[1] & 0x1fe0) == 0x0f00)   /* 32 bit Trap gate */
                SegType = "TRAPGATE32";
            else if ((SegDesc[1] & 0x1fe0) == 0x0700)   /* 16 bit Trap gate */
                SegType = "TRAPGATE16";
            else
                SegType = "UNKNOWN";

            if ((SegDesc[1] & (1 << 15)) == 0) /* not present */
            {
                KdbpPrint("  %03d  %-10s  [NP]       [NP]        %02d\n",
                          i / 8, SegType, Dpl);
            }
            else if ((SegDesc[1] & 0x1f00) == 0x0500) /* Task gate */
            {
                SegSel = SegDesc[0] >> 16;
                KdbpPrint("  %03d  %-10s  0x%04x                 %02d\n",
                          i / 8, SegType, SegSel, Dpl);
            }
            else
            {
                SegSel = SegDesc[0] >> 16;
                SegBase = (SegDesc[1] & 0xffff0000) | (SegDesc[0] & 0x0000ffff);
                KdbpPrint("  %03d  %-10s  0x%04x     0x%08x  %02d\n",
                          i / 8, SegType, SegSel, SegBase, Dpl);
            }
        }
    }
    else
    {
        ul = 0;

        if (Argv[0][0] == 'g')
        {
            /* Read GDTR */
            Ke386GetGlobalDescriptorTable(&Reg.Limit);
            i = 8;
        }
        else
        {
            ASSERT(Argv[0][0] == 'l');

            /* Read LDTR */
            Reg.Limit = Ke386GetLocalDescriptorTable();
            Reg.Base = 0;
            i = 0;
            ul = 1 << 2;
        }

        if (Reg.Limit < 7)
        {
            KdbpPrint("%s descriptor table is empty.\n",
                      Argv[0][0] == 'g' ? "Global" : "Local");
            return TRUE;
        }

        KdbpPrint("%cDT Base: 0x%08x  Limit: 0x%04x\n",
                  Argv[0][0] == 'g' ? 'G' : 'L', Reg.Base, Reg.Limit);
        KdbpPrint("  Idx  Sel.    Type         Base        Limit       DPL  Attribs\n");

        for (; (i + sizeof(SegDesc) - 1) <= Reg.Limit; i += 8)
        {
            if (!NT_SUCCESS(KdbpSafeReadMemory(SegDesc, (PVOID)(Reg.Base + i), sizeof(SegDesc))))
            {
                KdbpPrint("Couldn't access memory at 0x%08x!\n", Reg.Base + i);
                return TRUE;
            }

            Dpl = ((SegDesc[1] >> 13) & 3);
            Type = ((SegDesc[1] >> 8) & 0xf);

            SegBase = SegDesc[0] >> 16;
            SegBase |= (SegDesc[1] & 0xff) << 16;
            SegBase |= SegDesc[1] & 0xff000000;
            SegLimit = SegDesc[0] & 0x0000ffff;
            SegLimit |= (SegDesc[1] >> 16) & 0xf;

            if ((SegDesc[1] & (1 << 23)) != 0)
            {
                SegLimit *= 4096;
                SegLimit += 4095;
            }
            else
            {
                SegLimit++;
            }

            if ((SegDesc[1] & (1 << 12)) == 0) /* System segment */
            {
                switch (Type)
                {
                    case 1: SegType = "TSS16(Avl)"; break;
                    case 2: SegType = "LDT"; break;
                    case 3: SegType = "TSS16(Busy)"; break;
                    case 4: SegType = "CALLGATE16"; break;
                    case 5: SegType = "TASKGATE"; break;
                    case 6: SegType = "INTGATE16"; break;
                    case 7: SegType = "TRAPGATE16"; break;
                    case 9: SegType = "TSS32(Avl)"; break;
                    case 11: SegType = "TSS32(Busy)"; break;
                    case 12: SegType = "CALLGATE32"; break;
                    case 14: SegType = "INTGATE32"; break;
                    case 15: SegType = "INTGATE32"; break;
                    default: SegType = "UNKNOWN"; break;
                }

                if (!(Type >= 1 && Type <= 3) &&
                    Type != 9 && Type != 11)
                {
                    SegBase = 0;
                    SegLimit = 0;
                }
            }
            else if ((SegDesc[1] & (1 << 11)) == 0) /* Data segment */
            {
                if ((SegDesc[1] & (1 << 22)) != 0)
                    SegType = "DATA32";
                else
                    SegType = "DATA16";
            }
            else /* Code segment */
            {
                if ((SegDesc[1] & (1 << 22)) != 0)
                    SegType = "CODE32";
                else
                    SegType = "CODE16";
            }

            if ((SegDesc[1] & (1 << 15)) == 0) /* not present */
            {
                KdbpPrint("  %03d  0x%04x  %-11s  [NP]        [NP]        %02d   NP\n",
                          i / 8, i | Dpl | ul, SegType, Dpl);
            }
            else
            {
                KdbpPrint("  %03d  0x%04x  %-11s  0x%08x  0x%08x  %02d  ",
                          i / 8, i | Dpl | ul, SegType, SegBase, SegLimit, Dpl);

                if ((SegDesc[1] & (1 << 12)) == 0) /* System segment */
                {
                    /* FIXME: Display system segment */
                }
                else if ((SegDesc[1] & (1 << 11)) == 0) /* Data segment */
                {
                    if ((SegDesc[1] & (1 << 10)) != 0) /* Expand-down */
                        KdbpPrint(" E");

                    KdbpPrint((SegDesc[1] & (1 << 9)) ? " R/W" : " R");

                    if ((SegDesc[1] & (1 << 8)) != 0)
                        KdbpPrint(" A");
                }
                else /* Code segment */
                {
                    if ((SegDesc[1] & (1 << 10)) != 0) /* Conforming */
                        KdbpPrint(" C");

                    KdbpPrint((SegDesc[1] & (1 << 9)) ? " R/X" : " X");

                    if ((SegDesc[1] & (1 << 8)) != 0)
                        KdbpPrint(" A");
                }

                if ((SegDesc[1] & (1 << 20)) != 0)
                    KdbpPrint(" AVL");

                KdbpPrint("\n");
            }
        }
    }

    return TRUE;
}