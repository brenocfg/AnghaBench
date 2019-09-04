#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int ULONG ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ length; } ;
typedef  TYPE_1__ NE_NAMEINFO ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static BYTE * USER32_LoadResource( LPBYTE peimage, NE_NAMEINFO* pNInfo, WORD sizeShift, ULONG *uSize)
{
	TRACE("%p %p 0x%08x\n", peimage, pNInfo, sizeShift);

	*uSize = (DWORD)pNInfo->length << sizeShift;
	return peimage + ((DWORD)pNInfo->offset << sizeShift);
}