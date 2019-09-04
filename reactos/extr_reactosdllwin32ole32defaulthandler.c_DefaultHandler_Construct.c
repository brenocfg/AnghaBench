#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int inproc_server; int ref; int /*<<< orphan*/ * pCFObject; int /*<<< orphan*/  object_state; int /*<<< orphan*/ * pDataDelegate; int /*<<< orphan*/ * pOleDelegate; int /*<<< orphan*/ * pPSDelegate; int /*<<< orphan*/  clsid; int /*<<< orphan*/  storage_state; int /*<<< orphan*/ * storage; scalar_t__ dwAdvConn; scalar_t__ in_call; int /*<<< orphan*/ * containerObj; int /*<<< orphan*/ * containerApp; int /*<<< orphan*/ * dataAdviseHolder; int /*<<< orphan*/ * oleAdviseHolder; int /*<<< orphan*/ * clientSite; TYPE_6__* dataCache; TYPE_6__* outerUnknown; int /*<<< orphan*/  dataCache_PersistStg; TYPE_6__ IUnknown_iface; TYPE_5__ IPersistStorage_iface; TYPE_4__ IAdviseSink_iface; TYPE_3__ IRunnableObject_iface; TYPE_2__ IDataObject_iface; TYPE_1__ IOleObject_iface; } ;
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  TYPE_6__* LPUNKNOWN ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_7__ DefaultHandler ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CreateDataCache (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  DefaultHandler_IAdviseSink_VTable ; 
 int /*<<< orphan*/  DefaultHandler_IDataObject_VTable ; 
 int /*<<< orphan*/  DefaultHandler_IOleObject_VTable ; 
 int /*<<< orphan*/  DefaultHandler_IPersistStorage_VTable ; 
 int /*<<< orphan*/  DefaultHandler_IRunnableObject_VTable ; 
 int /*<<< orphan*/  DefaultHandler_NDIUnknown_VTable ; 
 int EMBDHLP_DELAYCREATE ; 
 int EMBDHLP_INPROC_SERVER ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_7__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  IClassFactory_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDataObject ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IPersistStorage ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IOleObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (TYPE_6__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_6__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_state_not_running ; 
 int /*<<< orphan*/  object_state_running ; 
 int /*<<< orphan*/  storage_state_uninitialised ; 

__attribute__((used)) static DefaultHandler* DefaultHandler_Construct(
  REFCLSID  clsid,
  LPUNKNOWN pUnkOuter,
  DWORD flags,
  IClassFactory *pCF)
{
  DefaultHandler* This = NULL;
  HRESULT hr;

  This = HeapAlloc(GetProcessHeap(), 0, sizeof(DefaultHandler));

  if (!This)
    return This;

  This->IOleObject_iface.lpVtbl = &DefaultHandler_IOleObject_VTable;
  This->IUnknown_iface.lpVtbl = &DefaultHandler_NDIUnknown_VTable;
  This->IDataObject_iface.lpVtbl = &DefaultHandler_IDataObject_VTable;
  This->IRunnableObject_iface.lpVtbl = &DefaultHandler_IRunnableObject_VTable;
  This->IAdviseSink_iface.lpVtbl = &DefaultHandler_IAdviseSink_VTable;
  This->IPersistStorage_iface.lpVtbl = &DefaultHandler_IPersistStorage_VTable;

  This->inproc_server = (flags & EMBDHLP_INPROC_SERVER) != 0;

  /*
   * Start with one reference count. The caller of this function
   * must release the interface pointer when it is done.
   */
  This->ref = 1;

  /*
   * Initialize the outer unknown
   * We don't keep a reference on the outer unknown since, the way
   * aggregation works, our lifetime is at least as large as its
   * lifetime.
   */
  if (!pUnkOuter)
    pUnkOuter = &This->IUnknown_iface;

  This->outerUnknown = pUnkOuter;

  /*
   * Create a datacache object.
   * We aggregate with the datacache. Make sure we pass our outer
   * unknown as the datacache's outer unknown.
   */
  hr = CreateDataCache(This->outerUnknown,
                       clsid,
                       &IID_IUnknown,
                       (void**)&This->dataCache);
  if(SUCCEEDED(hr))
  {
    hr = IUnknown_QueryInterface(This->dataCache, &IID_IPersistStorage, (void**)&This->dataCache_PersistStg);
    /* keeping a reference to This->dataCache_PersistStg causes us to keep a
     * reference on the outer object */
    if (SUCCEEDED(hr))
        IUnknown_Release(This->outerUnknown);
    else
        IUnknown_Release(This->dataCache);
  }
  if(FAILED(hr))
  {
    ERR("Unexpected error creating data cache\n");
    HeapFree(GetProcessHeap(), 0, This);
    return NULL;
  }

  This->clsid = *clsid;
  This->clientSite = NULL;
  This->oleAdviseHolder = NULL;
  This->dataAdviseHolder = NULL;
  This->containerApp = NULL;
  This->containerObj = NULL;
  This->pOleDelegate = NULL;
  This->pPSDelegate = NULL;
  This->pDataDelegate = NULL;
  This->object_state = object_state_not_running;
  This->in_call = 0;

  This->dwAdvConn = 0;
  This->storage = NULL;
  This->storage_state = storage_state_uninitialised;

  if (This->inproc_server && !(flags & EMBDHLP_DELAYCREATE))
  {
    HRESULT hr;
    This->pCFObject = NULL;
    if (pCF)
      hr = IClassFactory_CreateInstance(pCF, NULL, &IID_IOleObject, (void **)&This->pOleDelegate);
    else
      hr = CoCreateInstance(&This->clsid, NULL, CLSCTX_INPROC_SERVER,
                            &IID_IOleObject, (void **)&This->pOleDelegate);
    if (SUCCEEDED(hr))
      hr = IOleObject_QueryInterface(This->pOleDelegate, &IID_IPersistStorage, (void **)&This->pPSDelegate);
    if (SUCCEEDED(hr))
      hr = IOleObject_QueryInterface(This->pOleDelegate, &IID_IDataObject, (void **)&This->pDataDelegate);
    if (SUCCEEDED(hr))
      This->object_state = object_state_running;
    if (FAILED(hr))
      WARN("object creation failed with error %08x\n", hr);
  }
  else
  {
    This->pCFObject = pCF;
    if (pCF) IClassFactory_AddRef(pCF);
  }

  return This;
}