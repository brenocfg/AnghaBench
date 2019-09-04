#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct channel_hook_entry {int /*<<< orphan*/  entry; int /*<<< orphan*/ * hook; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/ * REFGUID ;
typedef  int /*<<< orphan*/  IChannelHook ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct channel_hook_entry* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IChannelHook_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_hooks ; 
 int /*<<< orphan*/  csChannelHook ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT RPC_RegisterChannelHook(REFGUID rguid, IChannelHook *hook)
{
    struct channel_hook_entry *entry;

    TRACE("(%s, %p)\n", debugstr_guid(rguid), hook);

    entry = HeapAlloc(GetProcessHeap(), 0, sizeof(*entry));
    if (!entry)
        return E_OUTOFMEMORY;

    entry->id = *rguid;
    entry->hook = hook;
    IChannelHook_AddRef(hook);

    EnterCriticalSection(&csChannelHook);
    list_add_tail(&channel_hooks, &entry->entry);
    LeaveCriticalSection(&csChannelHook);

    return S_OK;
}