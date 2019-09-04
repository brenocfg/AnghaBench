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
struct TYPE_2__ {int /*<<< orphan*/  used; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * CONTAINING_RECORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLAYX_MEM_SLICE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  data ; 
 int dwBlockSize ; 
 TYPE_1__* lpMemArea ; 

__attribute__((used)) static void DPLAYX_PrivHeapFree( LPVOID addr )
{
  LPVOID lpAddrStart;
  DWORD dwBlockUsed;

  /* Handle getting passed a NULL */
  if( addr == NULL )
  {
    return;
  }

  lpAddrStart = CONTAINING_RECORD(addr, DPLAYX_MEM_SLICE, data); /* Find block header */
  dwBlockUsed =  ((BYTE*)lpAddrStart - (BYTE*)lpMemArea)/dwBlockSize;

  lpMemArea[ dwBlockUsed ].used = FALSE;
}