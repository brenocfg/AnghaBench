#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ipid; } ;
struct ifproxy {TYPE_3__* parent; int /*<<< orphan*/  refs; TYPE_1__ stdobjref; } ;
struct TYPE_7__ {int /*<<< orphan*/  remoting_mutex; int /*<<< orphan*/  oid; int /*<<< orphan*/  oxid; } ;
struct TYPE_6__ {scalar_t__ cPrivateRefs; int /*<<< orphan*/  cPublicRefs; int /*<<< orphan*/  ipid; } ;
typedef  TYPE_2__ REMINTERFACEREF ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IRemUnknown ;
typedef  struct ifproxy* HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,struct ifproxy*) ; 
 struct ifproxy* E_UNEXPECTED ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IRemUnknown_Release (int /*<<< orphan*/ *) ; 
 struct ifproxy* IRemUnknown_RemRelease (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  InterlockedExchangeAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ifproxy* RPC_E_DISCONNECTED ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 struct ifproxy* S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifproxy* proxy_manager_get_remunknown (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT ifproxy_release_public_refs(struct ifproxy * This)
{
    HRESULT hr = S_OK;
    LONG public_refs;

    if (WAIT_OBJECT_0 != WaitForSingleObject(This->parent->remoting_mutex, INFINITE))
    {
        ERR("Wait failed for ifproxy %p\n", This);
        return E_UNEXPECTED;
    }

    public_refs = This->refs;
    if (public_refs > 0)
    {
        IRemUnknown *remunk = NULL;

        TRACE("releasing %d refs\n", public_refs);

        hr = proxy_manager_get_remunknown(This->parent, &remunk);
        if (hr == S_OK)
        {
            REMINTERFACEREF rif;
            rif.ipid = This->stdobjref.ipid;
            rif.cPublicRefs = public_refs;
            rif.cPrivateRefs = 0;
            hr = IRemUnknown_RemRelease(remunk, 1, &rif);
            IRemUnknown_Release(remunk);
            if (hr == S_OK)
                InterlockedExchangeAdd((LONG *)&This->refs, -public_refs);
            else if (hr == RPC_E_DISCONNECTED)
                WARN("couldn't release references because object was "
                     "disconnected: oxid = %s, oid = %s\n",
                     wine_dbgstr_longlong(This->parent->oxid),
                     wine_dbgstr_longlong(This->parent->oid));
            else
                ERR("IRemUnknown_RemRelease failed with error 0x%08x\n", hr);
        }
    }
    ReleaseMutex(This->parent->remoting_mutex);

    return hr;
}