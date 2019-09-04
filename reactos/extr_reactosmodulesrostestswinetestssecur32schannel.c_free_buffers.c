#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* pvBuffer; } ;
struct TYPE_4__ {TYPE_3__* pBuffers; } ;
typedef  TYPE_1__ SecBufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void free_buffers(SecBufferDesc *desc)
{
    HeapFree(GetProcessHeap(), 0, desc->pBuffers[0].pvBuffer);
    HeapFree(GetProcessHeap(), 0, desc->pBuffers);
}