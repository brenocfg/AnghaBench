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
typedef  char* PWCHAR ;
typedef  int INTERFACE_TYPE ;

/* Variables and functions */
#define  CBus 143 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
#define  Eisa 142 
#define  Internal 141 
#define  Isa 140 
#define  MPIBus 139 
#define  MPSABus 138 
#define  MicroChannel 137 
#define  NuBus 136 
#define  PCIBus 135 
#define  PCMCIABus 134 
#define  PNPBus 133 
#define  PNPISABus 132 
#define  ProcessorInternal 131 
#define  TurboChannel 130 
#define  VMEBus 129 
#define  Vmcs 128 

PWCHAR
IopGetInterfaceTypeString(INTERFACE_TYPE IfType)
{
    switch (IfType)
    {
       case Internal:
         return L"Internal";

       case Isa:
         return L"Isa";

       case Eisa:
         return L"Eisa";

       case MicroChannel:
         return L"MicroChannel";

       case TurboChannel:
         return L"TurboChannel";

       case PCIBus:
         return L"PCIBus";

       case VMEBus:
         return L"VMEBus";

       case NuBus:
         return L"NuBus";

       case PCMCIABus:
         return L"PCMCIABus";

       case CBus:
         return L"CBus";

       case MPIBus:
         return L"MPIBus";

       case MPSABus:
         return L"MPSABus";

       case ProcessorInternal:
         return L"ProcessorInternal";

       case PNPISABus:
         return L"PNPISABus";

       case PNPBus:
         return L"PNPBus";

       case Vmcs:
         return L"Vmcs";

       default:
         DPRINT1("Invalid bus type: %d\n", IfType);
         return NULL;
    }
}