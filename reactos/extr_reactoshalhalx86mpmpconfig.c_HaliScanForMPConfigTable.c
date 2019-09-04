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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {scalar_t__ Signature; int Length; int Specification; int Feature2; int Feature1; } ;
typedef  scalar_t__ PULONG ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_1__ MP_FLOATING_POINTER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int FEATURE2_IMCRP ; 
 scalar_t__ MPChecksum (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MPF_SIGNATURE ; 
 TYPE_1__* Mpf ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
HaliScanForMPConfigTable(ULONG Base,
			 ULONG Size)
{
/*
   PARAMETERS:
      Base = Base address of region
      Size = Length of region to check
   RETURNS:
      TRUE if a valid MP configuration table was found
 */

   PULONG bp = (PULONG)Base;
   MP_FLOATING_POINTER* mpf;
   UCHAR Checksum;

   while (Size > 0)
   {
      mpf = (MP_FLOATING_POINTER*)bp;
      if (mpf->Signature == MPF_SIGNATURE)
      {
	 Checksum = MPChecksum((PUCHAR)bp, 16);
	 DPRINT("Found MPF signature at %x, checksum %x\n", bp, Checksum);
         if (Checksum == 0 &&
	     mpf->Length == 1)
         {
            DPRINT("Intel MultiProcessor Specification v1.%d compliant system.\n",
                   mpf->Specification);

            if (mpf->Feature2 & FEATURE2_IMCRP) 
	    {
               DPRINT("Running in IMCR and PIC compatibility mode.\n");
            } 
	    else 
	    {
               DPRINT("Running in Virtual Wire compatibility mode.\n");
	    }
	

            switch (mpf->Feature1)
            {
               case 0:
                  /* Non standard configuration */
                  break;
               case 1:
                  DPRINT("ISA\n");
                  break;
               case 2:
                  DPRINT("EISA with no IRQ8 chaining\n");
                  break;
               case 3:
                  DPRINT("EISA\n");
                  break;
               case 4:
                  DPRINT("MCA\n");
                  break;
               case 5:
                  DPRINT("ISA and PCI\n");
                  break;
               case 6:
                  DPRINT("EISA and PCI\n");
                  break;
               case 7:
                  DPRINT("MCA and PCI\n");
                  break;
               default:
                  DPRINT("Unknown standard configuration %d\n", mpf->Feature1);
                  return FALSE;
            }
            Mpf = mpf; 
            return TRUE;
         }
      }
      bp += 4;
      Size -= 16;
   }
   return FALSE;
}