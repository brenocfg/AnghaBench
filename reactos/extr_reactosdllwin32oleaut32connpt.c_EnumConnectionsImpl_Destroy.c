#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t nConns; struct TYPE_4__* pCD; int /*<<< orphan*/  pUnk; } ;
typedef  TYPE_1__ EnumConnectionsImpl ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EnumConnectionsImpl_Destroy(EnumConnectionsImpl *Obj)
{
  DWORD i;

  for(i = 0; i < Obj->nConns; i++)
    IUnknown_Release(Obj->pCD[i].pUnk);

  HeapFree(GetProcessHeap(), 0, Obj->pCD);
  HeapFree(GetProcessHeap(), 0, Obj);
  return;
}