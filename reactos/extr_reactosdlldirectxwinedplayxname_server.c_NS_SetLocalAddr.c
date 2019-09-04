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
typedef  TYPE_1__* lpNSCache ;
struct TYPE_2__ {int /*<<< orphan*/  lpLocalAddrHdr; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void NS_SetLocalAddr( LPVOID lpNSInfo, LPCVOID lpHdr, DWORD dwHdrSize )
{
  lpNSCache lpCache = (lpNSCache)lpNSInfo;

  lpCache->lpLocalAddrHdr = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwHdrSize );

  CopyMemory( lpCache->lpLocalAddrHdr, lpHdr, dwHdrSize );
}