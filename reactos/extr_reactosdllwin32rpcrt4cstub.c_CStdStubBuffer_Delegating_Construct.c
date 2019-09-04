#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int RefCount; int /*<<< orphan*/  pPSFactory; int /*<<< orphan*/ * pvServerObject; int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_2__ stub_buffer; int /*<<< orphan*/  base_obj; int /*<<< orphan*/  base_stub; } ;
typedef  TYPE_3__ cstdstubbuffer_delegating_t ;
struct TYPE_8__ {int /*<<< orphan*/  DispatchTableCount; int /*<<< orphan*/  piid; } ;
struct TYPE_11__ {int /*<<< orphan*/  Vtbl; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  PCInterfaceName ;
typedef  int /*<<< orphan*/  LPUNKNOWN ;
typedef  scalar_t__ LPRPCSTUBBUFFER ;
typedef  int /*<<< orphan*/  LPPSFACTORYBUFFER ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ CInterfaceStubVtbl ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IPSFactoryBuffer_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_E_UNEXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  create_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_delegating_vtbl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_delegating_vtbl (int /*<<< orphan*/ ) ; 

HRESULT CStdStubBuffer_Delegating_Construct(REFIID riid,
                                            LPUNKNOWN pUnkServer,
                                            PCInterfaceName name,
                                            CInterfaceStubVtbl *vtbl,
                                            REFIID delegating_iid,
                                            LPPSFACTORYBUFFER pPSFactory,
                                            LPRPCSTUBBUFFER *ppStub)
{
    cstdstubbuffer_delegating_t *This;
    IUnknown *pvServer;
    HRESULT r;

    TRACE("(%p,%p,%p,%p) %s\n", pUnkServer, vtbl, pPSFactory, ppStub, name);
    TRACE("iid=%s delegating to %s\n", debugstr_guid(vtbl->header.piid), debugstr_guid(delegating_iid));
    TRACE("vtbl=%p\n", &vtbl->Vtbl);

    if (!IsEqualGUID(vtbl->header.piid, riid))
    {
        ERR("IID mismatch during stub creation\n");
        return RPC_E_UNEXPECTED;
    }

    r = IUnknown_QueryInterface(pUnkServer, riid, (void**)&pvServer);
    if(FAILED(r)) return r;

    This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*This));
    if (!This)
    {
        IUnknown_Release(pvServer);
        return E_OUTOFMEMORY;
    }

    This->base_obj = get_delegating_vtbl( vtbl->header.DispatchTableCount );
    r = create_stub(delegating_iid, (IUnknown*)&This->base_obj, &This->base_stub);
    if(FAILED(r))
    {
        release_delegating_vtbl(This->base_obj);
        HeapFree(GetProcessHeap(), 0, This);
        IUnknown_Release(pvServer);
        return r;
    }

    This->stub_buffer.lpVtbl = &vtbl->Vtbl;
    This->stub_buffer.RefCount = 1;
    This->stub_buffer.pvServerObject = pvServer;
    This->stub_buffer.pPSFactory = pPSFactory;
    *ppStub = (LPRPCSTUBBUFFER)&This->stub_buffer;

    IPSFactoryBuffer_AddRef(pPSFactory);
    return S_OK;
}