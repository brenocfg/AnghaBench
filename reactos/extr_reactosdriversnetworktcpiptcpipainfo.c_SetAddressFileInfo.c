#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_8__ {void* HeaderIncl; void* BCast; void* DF; int /*<<< orphan*/  TTL; } ;
struct TYPE_7__ {int toi_id; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  TYPE_1__ TDIObjectID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  void** PUINT ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_2__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
#define  AO_OPTION_BROADCAST 131 
#define  AO_OPTION_IP_DONTFRAGMENT 130 
#define  AO_OPTION_IP_HDRINCL 129 
#define  AO_OPTION_TTL 128 
 int /*<<< orphan*/  DbgPrint (char*,int) ; 
 int /*<<< orphan*/  LockObject (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TDI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 
 int /*<<< orphan*/  TDI_SUCCESS ; 
 int /*<<< orphan*/  UnlockObject (TYPE_2__*,int /*<<< orphan*/ ) ; 

TDI_STATUS SetAddressFileInfo(TDIObjectID *ID,
                              PADDRESS_FILE AddrFile,
                              PVOID Buffer,
                              UINT BufferSize)
{
    KIRQL OldIrql;

    switch (ID->toi_id)
    {
      case AO_OPTION_TTL:
         if (BufferSize < sizeof(UINT))
             return TDI_INVALID_PARAMETER;

         LockObject(AddrFile, &OldIrql);
         AddrFile->TTL = *((PUCHAR)Buffer);
         UnlockObject(AddrFile, OldIrql);

         return TDI_SUCCESS;

      case AO_OPTION_IP_DONTFRAGMENT:
         if (BufferSize < sizeof(UINT))
             return TDI_INVALID_PARAMETER;

         LockObject(AddrFile, &OldIrql);
         AddrFile->DF = *((PUINT)Buffer);
         UnlockObject(AddrFile, OldIrql);

         return TDI_SUCCESS;

      case AO_OPTION_BROADCAST:
         if (BufferSize < sizeof(UINT))
             return TDI_INVALID_PARAMETER;

         LockObject(AddrFile, &OldIrql);
         AddrFile->BCast = *((PUINT)Buffer);
         UnlockObject(AddrFile, OldIrql);

         return TDI_SUCCESS;

      case AO_OPTION_IP_HDRINCL:
         if (BufferSize < sizeof(UINT))
             return TDI_INVALID_PARAMETER;

         LockObject(AddrFile, &OldIrql);
         AddrFile->HeaderIncl = *((PUINT)Buffer);
         UnlockObject(AddrFile, OldIrql);

         return TDI_SUCCESS;

      default:
         DbgPrint("Unimplemented option %x\n", ID->toi_id);

         return TDI_INVALID_REQUEST;
    }
}