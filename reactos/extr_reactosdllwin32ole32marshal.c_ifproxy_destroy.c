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
struct ifproxy {scalar_t__ proxy; int /*<<< orphan*/ * chan; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifproxy*) ; 
 int /*<<< orphan*/  IRpcChannelBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRpcProxyBuffer_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,struct ifproxy*) ; 
 int /*<<< orphan*/  ifproxy_release_public_refs (struct ifproxy*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ifproxy_destroy(struct ifproxy * This)
{
    TRACE("%p\n", This);

    /* release public references to this object so that the stub can know
     * when to destroy itself */
    ifproxy_release_public_refs(This);

    list_remove(&This->entry);

    if (This->chan)
    {
        IRpcChannelBuffer_Release(This->chan);
        This->chan = NULL;
    }

    if (This->proxy) IRpcProxyBuffer_Release(This->proxy);

    HeapFree(GetProcessHeap(), 0, This);
}