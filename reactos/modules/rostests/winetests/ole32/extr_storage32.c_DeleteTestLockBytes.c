#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; struct TYPE_7__* contents; TYPE_1__ ILockBytes_iface; } ;
typedef  TYPE_2__ TestLockBytes ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TestLockBytes_Vtbl ; 
 int /*<<< orphan*/  ok (int,char*,TYPE_2__*,...) ; 

__attribute__((used)) static void DeleteTestLockBytes(TestLockBytes *This)
{
    ok(This->ILockBytes_iface.lpVtbl == &TestLockBytes_Vtbl, "test lock bytes %p deleted with incorrect vtable\n", This);
    ok(This->ref == 1, "test lock bytes %p deleted with %i references instead of 1\n", This, This->ref);
    HeapFree(GetProcessHeap(), 0, This->contents);
    HeapFree(GetProcessHeap(), 0, This);
}