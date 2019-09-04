#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* taskName; struct TYPE_5__* parameters; struct TYPE_5__* comment; struct TYPE_5__* accountName; } ;
typedef  TYPE_1__ TaskImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  dll_ref ; 

__attribute__((used)) static void TaskDestructor(TaskImpl *This)
{
    TRACE("%p\n", This);
    HeapFree(GetProcessHeap(), 0, This->accountName);
    HeapFree(GetProcessHeap(), 0, This->comment);
    HeapFree(GetProcessHeap(), 0, This->parameters);
    HeapFree(GetProcessHeap(), 0, This->taskName);
    HeapFree(GetProcessHeap(), 0, This);
    InterlockedDecrement(&dll_ref);
}