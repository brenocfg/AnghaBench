#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIServiceManager ;
typedef  int /*<<< orphan*/  nsIComponentRegistrar ;
struct TYPE_4__ {int /*<<< orphan*/  nsIFactory_iface; } ;
struct TYPE_3__ {int /*<<< orphan*/  nsIFactory_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_PROMPTSERVICE_CID ; 
 int /*<<< orphan*/  NS_PROMPTSERVICE_CONTRACTID ; 
 int /*<<< orphan*/  NS_TOOLTIPTEXTPROVIDER_CID ; 
 char* NS_TOOLTIPTEXTPROVIDER_CLASSNAME ; 
 int /*<<< orphan*/  NS_TOOLTIPTEXTPROVIDER_CONTRACTID ; 
 int /*<<< orphan*/  nsIComponentRegistrar_RegisterFactory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ nsPromptServiceFactory ; 
 TYPE_1__ nsTooltipTextFactory ; 

void register_nsservice(nsIComponentRegistrar *registrar, nsIServiceManager *service_manager)
{
    nsresult nsres;

    nsres = nsIComponentRegistrar_RegisterFactory(registrar, &NS_PROMPTSERVICE_CID,
            "Prompt Service", NS_PROMPTSERVICE_CONTRACTID, &nsPromptServiceFactory.nsIFactory_iface);
    if(NS_FAILED(nsres))
        ERR("RegisterFactory failed: %08x\n", nsres);

    nsres = nsIComponentRegistrar_RegisterFactory(registrar, &NS_TOOLTIPTEXTPROVIDER_CID,
            NS_TOOLTIPTEXTPROVIDER_CLASSNAME, NS_TOOLTIPTEXTPROVIDER_CONTRACTID,
            &nsTooltipTextFactory.nsIFactory_iface);
    if(NS_FAILED(nsres))
        ERR("RegisterFactory failed: %08x\n", nsres);
}