#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pIUnknown; } ;
struct TYPE_6__ {TYPE_1__ interfaces; int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ Sink ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_sink(Sink *sink)
{
    list_remove(&sink->entry);
    IUnknown_Release(sink->interfaces.pIUnknown);
    HeapFree(GetProcessHeap(), 0, sink);
}