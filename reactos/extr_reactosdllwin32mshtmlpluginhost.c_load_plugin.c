#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  plugin_unk; } ;
typedef  TYPE_1__ PluginHost ;
typedef  int /*<<< orphan*/  IPersistPropertyBag2 ;
typedef  int /*<<< orphan*/  IPersistPropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_IPersistPropertyBag ; 
 int /*<<< orphan*/  IID_IPersistPropertyBag2 ; 
 int /*<<< orphan*/  IPersistPropertyBag2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistPropertyBag_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_prop_bag (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_plugin(PluginHost *host)
{
    IPersistPropertyBag2 *persist_prop_bag2;
    IPersistPropertyBag *persist_prop_bag;
    HRESULT hres;

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IPersistPropertyBag2, (void**)&persist_prop_bag2);
    if(SUCCEEDED(hres)) {
        FIXME("Use IPersistPropertyBag2 iface\n");
        IPersistPropertyBag2_Release(persist_prop_bag2);
        return;
    }

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IPersistPropertyBag, (void**)&persist_prop_bag);
    if(SUCCEEDED(hres)) {
        load_prop_bag(host, persist_prop_bag);
        IPersistPropertyBag_Release(persist_prop_bag);
        return;
    }

    FIXME("No IPersistPropertyBag iface\n");
}