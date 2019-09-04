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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  scalar_t__* PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  scalar_t__ PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CopyBufferToBufferChain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TDI_SUCCESS ; 

TDI_STATUS InfoCopyOut( PCHAR DataOut, UINT SizeOut,
			PNDIS_BUFFER ClientBuf, PUINT ClientBufSize ) {
    UINT RememberedCBSize = *ClientBufSize;
    *ClientBufSize = SizeOut;

    /* The driver returns success even when it couldn't fit every available
     * byte. */
    if( RememberedCBSize < SizeOut || !ClientBuf )
	return TDI_SUCCESS;
    else {
	CopyBufferToBufferChain( ClientBuf, 0, (PCHAR)DataOut, SizeOut );
	return TDI_SUCCESS;
    }
}