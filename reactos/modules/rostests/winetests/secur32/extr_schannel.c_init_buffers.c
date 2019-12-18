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
struct TYPE_5__ {unsigned int cBuffers; TYPE_1__* pBuffers; int /*<<< orphan*/  ulVersion; } ;
struct TYPE_4__ {unsigned int cbBuffer; void* pvBuffer; } ;
typedef  TYPE_2__ SecBufferDesc ;
typedef  int /*<<< orphan*/  SecBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SECBUFFER_VERSION ; 

__attribute__((used)) static void init_buffers(SecBufferDesc *desc, unsigned count, unsigned size)
{
    desc->ulVersion = SECBUFFER_VERSION;
    desc->cBuffers = count;
    desc->pBuffers = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, count*sizeof(SecBuffer));

    desc->pBuffers[0].cbBuffer = size;
    desc->pBuffers[0].pvBuffer = HeapAlloc(GetProcessHeap(), 0, size);
}