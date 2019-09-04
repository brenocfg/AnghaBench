#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ipidRemUnknown; } ;
struct stub_manager {int /*<<< orphan*/  lock; int /*<<< orphan*/  norm_refs; int /*<<< orphan*/  ifstubs; TYPE_1__ oxid_info; int /*<<< orphan*/  object; int /*<<< orphan*/  oid; } ;
struct ifstub {int flags; int /*<<< orphan*/  ipid; int /*<<< orphan*/  entry; int /*<<< orphan*/  iid; int /*<<< orphan*/ * stubbuffer; int /*<<< orphan*/  iface; int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int MSHLFLAGS ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct ifstub* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifstub*) ; 
 int /*<<< orphan*/  IRpcStubBuffer_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MSHLFLAGSP_REMUNKNOWN ; 
 int MSHLFLAGS_NORMAL ; 
 scalar_t__ RPC_CreateServerChannel (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct ifstub*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_ipid (struct stub_manager*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

struct ifstub *stub_manager_new_ifstub(struct stub_manager *m, IRpcStubBuffer *sb, REFIID iid, DWORD dest_context,
    void *dest_context_data, MSHLFLAGS flags)
{
    struct ifstub *stub;
    HRESULT hr;

    TRACE("oid=%s, stubbuffer=%p, iid=%s, dest_context=%x\n", wine_dbgstr_longlong(m->oid), sb,
          debugstr_guid(iid), dest_context);

    stub = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct ifstub));
    if (!stub) return NULL;

    hr = IUnknown_QueryInterface(m->object, iid, (void **)&stub->iface);
    if (hr != S_OK)
    {
        HeapFree(GetProcessHeap(), 0, stub);
        return NULL;
    }

    hr = RPC_CreateServerChannel(dest_context, dest_context_data, &stub->chan);
    if (hr != S_OK)
    {
        IUnknown_Release(stub->iface);
        HeapFree(GetProcessHeap(), 0, stub);
        return NULL;
    }

    stub->stubbuffer = sb;
    if (sb) IRpcStubBuffer_AddRef(sb);

    stub->flags = flags;
    stub->iid = *iid;

    /* FIXME: find a cleaner way of identifying that we are creating an ifstub
     * for the remunknown interface */
    if (flags & MSHLFLAGSP_REMUNKNOWN)
        stub->ipid = m->oxid_info.ipidRemUnknown;
    else
        generate_ipid(m, &stub->ipid);

    EnterCriticalSection(&m->lock);
    list_add_head(&m->ifstubs, &stub->entry);
    /* every normal marshal is counted so we don't allow more than we should */
    if (flags & MSHLFLAGS_NORMAL) m->norm_refs++;
    LeaveCriticalSection(&m->lock);

    TRACE("ifstub %p created with ipid %s\n", stub, debugstr_guid(&stub->ipid));

    return stub;
}