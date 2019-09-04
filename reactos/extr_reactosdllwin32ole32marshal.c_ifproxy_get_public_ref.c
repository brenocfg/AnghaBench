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
struct ifproxy {scalar_t__ refs; TYPE_3__* parent; TYPE_1__ stdobjref; } ;
struct TYPE_7__ {int /*<<< orphan*/  remoting_mutex; } ;
struct TYPE_6__ {scalar_t__ cPrivateRefs; int /*<<< orphan*/  cPublicRefs; int /*<<< orphan*/  ipid; } ;
typedef  TYPE_2__ REMINTERFACEREF ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IRemUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IRemUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IRemUnknown_RemAddRef (int /*<<< orphan*/ *,int,TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  InterlockedExchangeAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORMALEXTREFS ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct ifproxy*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ proxy_manager_get_remunknown (TYPE_3__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT ifproxy_get_public_ref(struct ifproxy * This)
{
    HRESULT hr = S_OK;

    if (WAIT_OBJECT_0 != WaitForSingleObject(This->parent->remoting_mutex, INFINITE))
    {
        ERR("Wait failed for ifproxy %p\n", This);
        return E_UNEXPECTED;
    }

    if (This->refs == 0)
    {
        IRemUnknown *remunk = NULL;

        TRACE("getting public ref for ifproxy %p\n", This);

        hr = proxy_manager_get_remunknown(This->parent, &remunk);
        if (hr == S_OK)
        {
            HRESULT hrref = S_OK;
            REMINTERFACEREF rif;
            rif.ipid = This->stdobjref.ipid;
            rif.cPublicRefs = NORMALEXTREFS;
            rif.cPrivateRefs = 0;
            hr = IRemUnknown_RemAddRef(remunk, 1, &rif, &hrref);
            IRemUnknown_Release(remunk);
            if (hr == S_OK && hrref == S_OK)
                InterlockedExchangeAdd((LONG *)&This->refs, NORMALEXTREFS);
            else
                ERR("IRemUnknown_RemAddRef returned with 0x%08x, hrref = 0x%08x\n", hr, hrref);
        }
    }
    ReleaseMutex(This->parent->remoting_mutex);

    return hr;
}