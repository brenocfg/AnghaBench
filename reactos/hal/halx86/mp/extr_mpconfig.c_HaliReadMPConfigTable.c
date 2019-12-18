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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_3__ {scalar_t__ Signature; int Length; int Specification; int /*<<< orphan*/  LocalAPICAddress; int /*<<< orphan*/  ProductId; int /*<<< orphan*/  Oem; } ;
typedef  int* PUCHAR ;
typedef  TYPE_1__* PMP_CONFIGURATION_TABLE ;
typedef  int /*<<< orphan*/  PMP_CONFIGURATION_PROCESSOR ;
typedef  int /*<<< orphan*/  PMP_CONFIGURATION_IOAPIC ;
typedef  int /*<<< orphan*/  PMP_CONFIGURATION_INTSRC ;
typedef  int /*<<< orphan*/  PMP_CONFIGURATION_INTLOCAL ;
typedef  int /*<<< orphan*/  PMP_CONFIGURATION_BUS ;
typedef  int /*<<< orphan*/  MP_CONFIGURATION_TABLE ;
typedef  int /*<<< orphan*/  MP_CONFIGURATION_PROCESSOR ;
typedef  int /*<<< orphan*/  MP_CONFIGURATION_IOAPIC ;
typedef  int /*<<< orphan*/  MP_CONFIGURATION_INTSRC ;
typedef  int /*<<< orphan*/  MP_CONFIGURATION_INTLOCAL ;
typedef  int /*<<< orphan*/  MP_CONFIGURATION_BUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DEFAULT_BASE ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HAL_INITIALIZATION_FAILED ; 
 int /*<<< orphan*/  HaliMPBusInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HaliMPIOApicInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HaliMPIntLocalInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HaliMPIntSrcInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HaliMPProcessorInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeBugCheckEx (int /*<<< orphan*/ ,int,int,int,int) ; 
#define  MPCTE_BUS 132 
#define  MPCTE_INTSRC 131 
#define  MPCTE_IOAPIC 130 
#define  MPCTE_LINTSRC 129 
#define  MPCTE_PROCESSOR 128 
 scalar_t__ MPC_SIGNATURE ; 
 scalar_t__ MPChecksum (int*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
HaliReadMPConfigTable(PMP_CONFIGURATION_TABLE Table)
/*
   PARAMETERS:
      Table = Pointer to MP configuration table
 */
{
   PUCHAR Entry;
   ULONG Count;

   if (Table->Signature != MPC_SIGNATURE)
     {
       PUCHAR pc = (PUCHAR)&Table->Signature;
       
       DPRINT1("Bad MP configuration block signature: %c%c%c%c\n",
		pc[0], pc[1], pc[2], pc[3]);
       KeBugCheckEx(HAL_INITIALIZATION_FAILED, pc[0], pc[1], pc[2], pc[3]);
       return FALSE;
     }

   if (MPChecksum((PUCHAR)Table, Table->Length))
     {
       DPRINT1("Bad MP configuration block checksum\n");
       ASSERT(FALSE);
       return FALSE;
     }

   if (Table->Specification != 0x01 && Table->Specification != 0x04)
     {
       DPRINT1("Bad MP configuration table version (%d)\n",
	       Table->Specification);
       ASSERT(FALSE);
       return FALSE;
     }

   if (Table->LocalAPICAddress != APIC_DEFAULT_BASE)
     {
       DPRINT1("APIC base address is at 0x%X. I cannot handle non-standard adresses\n", 
	       Table->LocalAPICAddress);
       ASSERT(FALSE);
       return FALSE;
     }

   DPRINT("Oem: %.*s, ProductId: %.*s\n", 8, Table->Oem, 12, Table->ProductId);
   DPRINT("APIC at: %08x\n", Table->LocalAPICAddress);


   Entry = (PUCHAR)((ULONG_PTR)Table + sizeof(MP_CONFIGURATION_TABLE));
   Count = 0;
   while (Count < (Table->Length - sizeof(MP_CONFIGURATION_TABLE)))
   {
     /* Switch on type */
     switch (*Entry)
       {
       case MPCTE_PROCESSOR:
         {
	   HaliMPProcessorInfo((PMP_CONFIGURATION_PROCESSOR)Entry);
	   Entry += sizeof(MP_CONFIGURATION_PROCESSOR);
	   Count += sizeof(MP_CONFIGURATION_PROCESSOR);
	   break;
	 }
       case MPCTE_BUS:
	 {
	   HaliMPBusInfo((PMP_CONFIGURATION_BUS)Entry);
	   Entry += sizeof(MP_CONFIGURATION_BUS);
	   Count += sizeof(MP_CONFIGURATION_BUS);
	   break;
	 }
       case MPCTE_IOAPIC:
	 {
	   HaliMPIOApicInfo((PMP_CONFIGURATION_IOAPIC)Entry);
	   Entry += sizeof(MP_CONFIGURATION_IOAPIC);
	   Count += sizeof(MP_CONFIGURATION_IOAPIC);
	   break;
	 }
       case MPCTE_INTSRC:
	 {
	   HaliMPIntSrcInfo((PMP_CONFIGURATION_INTSRC)Entry);
	   Entry += sizeof(MP_CONFIGURATION_INTSRC);
	   Count += sizeof(MP_CONFIGURATION_INTSRC);
	   break;
	 }
       case MPCTE_LINTSRC:
	 {
	   HaliMPIntLocalInfo((PMP_CONFIGURATION_INTLOCAL)Entry);
	   Entry += sizeof(MP_CONFIGURATION_INTLOCAL);
	   Count += sizeof(MP_CONFIGURATION_INTLOCAL);
	   break;
	 }
       default:
	 DPRINT1("Unknown entry in MPC table\n");
	 ASSERT(FALSE);
	 return FALSE;
       }
   }
   return TRUE;
}