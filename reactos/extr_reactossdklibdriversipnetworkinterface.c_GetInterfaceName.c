#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_5__ {TYPE_1__ Name; } ;
typedef  TYPE_2__* PIP_INTERFACE ;
typedef  scalar_t__* PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlUnicodeToMultiByteN (scalar_t__*,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS GetInterfaceName( PIP_INTERFACE Interface,
			   PCHAR NameBuffer,
			   UINT Len ) {
    ULONG ResultSize = 0;
    NTSTATUS Status =
	RtlUnicodeToMultiByteN( NameBuffer,
				Len,
				&ResultSize,
				Interface->Name.Buffer,
				Interface->Name.Length );

    if( NT_SUCCESS(Status) )
	NameBuffer[ResultSize] = 0;
    else
	NameBuffer[0] = 0;

    return Status;
}