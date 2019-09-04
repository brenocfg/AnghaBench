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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int* PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyBufferToBufferChain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEBUG_INFO ; 
 int EntityCount ; 
 int /*<<< orphan*/ * EntityList ; 
 int /*<<< orphan*/  EntityListLock ; 
 int /*<<< orphan*/  TDI_SUCCESS ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

TDI_STATUS InfoTdiQueryListEntities(PNDIS_BUFFER Buffer,
				    PUINT BufferSize)
{
    UINT Count, Size, BufSize = *BufferSize;
    KIRQL OldIrql;

    TI_DbgPrint(DEBUG_INFO,("About to copy %d TDIEntityIDs to user\n",
			   EntityCount));

    TcpipAcquireSpinLock(&EntityListLock, &OldIrql);

    Size = EntityCount * sizeof(TDIEntityID);
    *BufferSize = Size;

    TI_DbgPrint(DEBUG_INFO,("BufSize: %d, NeededSize: %d\n", BufSize, Size));

    if (BufSize < Size || !Buffer)
    {
	TcpipReleaseSpinLock( &EntityListLock, OldIrql );
	/* The buffer is too small to contain requested data, but we return
         * success anyway, as we did everything we wanted. */
	return TDI_SUCCESS;
    }

    /* Return entity list -- Copy only the TDIEntityID parts. */
    for( Count = 0; Count < EntityCount; Count++ ) {
	CopyBufferToBufferChain(Buffer,
				Count * sizeof(TDIEntityID),
				(PCHAR)&EntityList[Count],
				sizeof(TDIEntityID));
    }

    TcpipReleaseSpinLock(&EntityListLock, OldIrql);

    return TDI_SUCCESS;
}