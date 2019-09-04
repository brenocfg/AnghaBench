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
struct TYPE_5__ {unsigned int cBuffers; TYPE_1__* pBuffers; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pvBuffer; scalar_t__ cbBuffer; int /*<<< orphan*/  BufferType; } ;
typedef  TYPE_2__ SecBufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  SECBUFFER_EMPTY ; 

__attribute__((used)) static void reset_buffers(SecBufferDesc *desc)
{
    unsigned i;

    for (i = 0; i < desc->cBuffers; ++i)
    {
        desc->pBuffers[i].BufferType = SECBUFFER_EMPTY;
        if (i > 0)
        {
            desc->pBuffers[i].cbBuffer = 0;
            desc->pBuffers[i].pvBuffer = NULL;
        }
    }
}