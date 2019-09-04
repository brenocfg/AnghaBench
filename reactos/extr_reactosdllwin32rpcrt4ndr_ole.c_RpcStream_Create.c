#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {scalar_t__ Buffer; } ;
struct TYPE_7__ {int RefCount; TYPE_3__ IStream_iface; scalar_t__* size; scalar_t__ pos; scalar_t__ data; TYPE_2__* pMsg; } ;
typedef  TYPE_1__ RpcStreamImpl ;
typedef  TYPE_2__* PMIDL_STUB_MESSAGE ;
typedef  scalar_t__* LPDWORD ;
typedef  TYPE_3__ IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RpcStream_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static HRESULT RpcStream_Create(PMIDL_STUB_MESSAGE pStubMsg, BOOL init, ULONG *size, IStream **stream)
{
  RpcStreamImpl *This;

  *stream = NULL;
  This = HeapAlloc(GetProcessHeap(), 0, sizeof(RpcStreamImpl));
  if (!This) return E_OUTOFMEMORY;
  This->IStream_iface.lpVtbl = &RpcStream_Vtbl;
  This->RefCount = 1;
  This->pMsg = pStubMsg;
  This->size = (LPDWORD)pStubMsg->Buffer;
  This->data = pStubMsg->Buffer + sizeof(DWORD);
  This->pos = 0;
  if (init) *This->size = 0;
  TRACE("init size=%d\n", *This->size);

  if (size) *size = *This->size;
  *stream = &This->IStream_iface;
  return S_OK;
}