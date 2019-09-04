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
typedef  int /*<<< orphan*/  policy ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_3__ {int /*<<< orphan*/  window; int /*<<< orphan*/  IInternetHostSecurityManager_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IClassFactoryEx ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CLSCTX_INPROC_SERVER ; 
 int CLSCTX_LOCAL_SERVER ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IClassFactoryEx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IClassFactory_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IClassFactoryEx ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IInternetHostSecurityManager_ProcessUrlAction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URLACTION_ACTIVEX_RUN ; 
 scalar_t__ URLPOLICY_ALLOW ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  check_codebase (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_elem_clsid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static IUnknown *create_activex_object(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, CLSID *clsid)
{
    IClassFactoryEx *cfex;
    IClassFactory *cf;
    IUnknown *obj;
    DWORD policy;
    HRESULT hres;

    if(!get_elem_clsid(nselem, clsid)) {
        WARN("Could not determine element CLSID\n");
        return NULL;
    }

    TRACE("clsid %s\n", debugstr_guid(clsid));

    policy = 0;
    hres = IInternetHostSecurityManager_ProcessUrlAction(&doc->IInternetHostSecurityManager_iface,
            URLACTION_ACTIVEX_RUN, (BYTE*)&policy, sizeof(policy), (BYTE*)clsid, sizeof(GUID), 0, 0);
    if(FAILED(hres) || policy != URLPOLICY_ALLOW) {
        WARN("ProcessUrlAction returned %08x %x\n", hres, policy);
        return NULL;
    }

    hres = CoGetClassObject(clsid, CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER, NULL, &IID_IClassFactory, (void**)&cf);
    if(hres == REGDB_E_CLASSNOTREG)
        check_codebase(doc->window, nselem);
    if(FAILED(hres))
        return NULL;

    hres = IClassFactory_QueryInterface(cf, &IID_IClassFactoryEx, (void**)&cfex);
    if(SUCCEEDED(hres)) {
        FIXME("Use IClassFactoryEx\n");
        IClassFactoryEx_Release(cfex);
    }

    hres = IClassFactory_CreateInstance(cf, NULL, &IID_IUnknown, (void**)&obj);
    IClassFactory_Release(cf);
    if(FAILED(hres))
        return NULL;

    return obj;
}