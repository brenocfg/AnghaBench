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
struct TYPE_5__ {scalar_t__ unk; } ;
struct TYPE_4__ {size_t sinks_size; TYPE_2__* sinks; } ;
typedef  size_t DWORD ;
typedef  TYPE_1__ ConnectionPoint ;

/* Variables and functions */
 int /*<<< orphan*/  IUnknown_Release (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static void ConnectionPoint_Destroy(ConnectionPoint *This)
{
    DWORD i;

    for(i=0; i<This->sinks_size; i++) {
        if(This->sinks[i].unk)
            IUnknown_Release(This->sinks[i].unk);
    }

    heap_free(This->sinks);
}