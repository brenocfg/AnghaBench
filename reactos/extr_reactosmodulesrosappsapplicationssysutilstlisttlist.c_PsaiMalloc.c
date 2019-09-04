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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtAllocateVirtualMemory (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 

void *PsaiMalloc(SIZE_T size)
{
 void * pBuf = NULL;
 NTSTATUS nErrCode;

 nErrCode = NtAllocateVirtualMemory
 (
  NtCurrentProcess(),
  &pBuf,
  0,
  &size,
  MEM_COMMIT,
  PAGE_READWRITE
 );

 if(NT_SUCCESS(nErrCode)) return pBuf;
 else return NULL;
}