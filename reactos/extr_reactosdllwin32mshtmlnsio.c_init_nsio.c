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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIFactory ;
typedef  int /*<<< orphan*/  nsIComponentRegistrar ;
typedef  int /*<<< orphan*/  nsIComponentManager ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIFactory ; 
 int /*<<< orphan*/  IID_nsIIOService ; 
 int /*<<< orphan*/  IID_nsINetUtil ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_IOSERVICE_CID ; 
 int /*<<< orphan*/  NS_IOSERVICE_CLASSNAME ; 
 int /*<<< orphan*/  NS_IOSERVICE_CONTRACTID ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_util ; 
 int /*<<< orphan*/  nsIComponentManager_GetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIComponentRegistrar_RegisterFactory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIComponentRegistrar_UnregisterFactory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIIOService_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIIOService_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIOServiceFactory ; 
 int /*<<< orphan*/  nsio ; 

void init_nsio(nsIComponentManager *component_manager, nsIComponentRegistrar *registrar)
{
    nsIFactory *old_factory = NULL;
    nsresult nsres;

    nsres = nsIComponentManager_GetClassObject(component_manager, &NS_IOSERVICE_CID,
                                               &IID_nsIFactory, (void**)&old_factory);
    if(NS_FAILED(nsres)) {
        ERR("Could not get factory: %08x\n", nsres);
        return;
    }

    nsres = nsIFactory_CreateInstance(old_factory, NULL, &IID_nsIIOService, (void**)&nsio);
    if(NS_FAILED(nsres)) {
        ERR("Couldn not create nsIOService instance %08x\n", nsres);
        nsIFactory_Release(old_factory);
        return;
    }

    nsres = nsIIOService_QueryInterface(nsio, &IID_nsINetUtil, (void**)&net_util);
    if(NS_FAILED(nsres)) {
        WARN("Could not get nsINetUtil interface: %08x\n", nsres);
        nsIIOService_Release(nsio);
        return;
    }

    nsres = nsIComponentRegistrar_UnregisterFactory(registrar, &NS_IOSERVICE_CID, old_factory);
    nsIFactory_Release(old_factory);
    if(NS_FAILED(nsres))
        ERR("UnregisterFactory failed: %08x\n", nsres);

    nsres = nsIComponentRegistrar_RegisterFactory(registrar, &NS_IOSERVICE_CID,
            NS_IOSERVICE_CLASSNAME, NS_IOSERVICE_CONTRACTID, &nsIOServiceFactory);
    if(NS_FAILED(nsres))
        ERR("RegisterFactory failed: %08x\n", nsres);
}