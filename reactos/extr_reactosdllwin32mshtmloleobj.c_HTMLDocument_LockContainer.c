#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ container_locked; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  IOleContainer ;
typedef  TYPE_1__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IOleClientSite_GetContainer (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOleContainer_LockContainer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IOleContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

void HTMLDocument_LockContainer(HTMLDocumentObj *This, BOOL fLock)
{
    IOleContainer *container;
    HRESULT hres;

    if(!This->client || This->container_locked == fLock)
        return;

    hres = IOleClientSite_GetContainer(This->client, &container);
    if(SUCCEEDED(hres)) {
        IOleContainer_LockContainer(container, fLock);
        This->container_locked = fLock;
        IOleContainer_Release(container);
    }
}