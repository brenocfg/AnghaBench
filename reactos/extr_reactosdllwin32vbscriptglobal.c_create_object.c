#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct CONFIRMSAFETY {scalar_t__ dwFlags; int /*<<< orphan*/ * pUnk; scalar_t__ clsid; } ;
struct TYPE_5__ {int safeopt; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  policy ;
typedef  int /*<<< orphan*/  cs ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IInternetHostSecurityManager ;
typedef  int /*<<< orphan*/  IClassFactoryEx ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ GUID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CLSCTX_INPROC_SERVER ; 
 int CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSIDFromProgID (int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  CoGetClassObject (scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GUID_CUSTOM_CONFIRMOBJECTSAFETY ; 
 int /*<<< orphan*/  IClassFactoryEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IClassFactoryEx ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IInternetHostSecurityManager_ProcessUrlAction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetHostSecurityManager_QueryCustomPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int INTERFACE_USES_SECURITY_MANAGER ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URLACTION_ACTIVEX_RUN ; 
 scalar_t__ URLPOLICY_ALLOW ; 
 scalar_t__ URLPOLICY_DISALLOW ; 
 int /*<<< orphan*/  debugstr_guid (scalar_t__*) ; 
 int /*<<< orphan*/ * get_sec_mgr (TYPE_1__*) ; 
 int /*<<< orphan*/  set_object_site (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static IUnknown *create_object(script_ctx_t *ctx, const WCHAR *progid)
{
    IInternetHostSecurityManager *secmgr = NULL;
    struct CONFIRMSAFETY cs;
    IClassFactoryEx *cfex;
    IClassFactory *cf;
    DWORD policy_size;
    BYTE *bpolicy;
    IUnknown *obj;
    DWORD policy;
    GUID guid;
    HRESULT hres;

    hres = CLSIDFromProgID(progid, &guid);
    if(FAILED(hres))
        return NULL;

    TRACE("GUID %s\n", debugstr_guid(&guid));

    if(ctx->safeopt & INTERFACE_USES_SECURITY_MANAGER) {
        secmgr = get_sec_mgr(ctx);
        if(!secmgr)
            return NULL;

        policy = 0;
        hres = IInternetHostSecurityManager_ProcessUrlAction(secmgr, URLACTION_ACTIVEX_RUN,
                (BYTE*)&policy, sizeof(policy), (BYTE*)&guid, sizeof(GUID), 0, 0);
        if(FAILED(hres) || policy != URLPOLICY_ALLOW)
            return NULL;
    }

    hres = CoGetClassObject(&guid, CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER, NULL, &IID_IClassFactory, (void**)&cf);
    if(FAILED(hres))
        return NULL;

    hres = IClassFactory_QueryInterface(cf, &IID_IClassFactoryEx, (void**)&cfex);
    if(SUCCEEDED(hres)) {
        FIXME("Use IClassFactoryEx\n");
        IClassFactoryEx_Release(cfex);
    }

    hres = IClassFactory_CreateInstance(cf, NULL, &IID_IUnknown, (void**)&obj);
    if(FAILED(hres))
        return NULL;

    if(secmgr) {
        cs.clsid = guid;
        cs.pUnk = obj;
        cs.dwFlags = 0;
        hres = IInternetHostSecurityManager_QueryCustomPolicy(secmgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
                &bpolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
        if(SUCCEEDED(hres)) {
            policy = policy_size >= sizeof(DWORD) ? *(DWORD*)bpolicy : URLPOLICY_DISALLOW;
            CoTaskMemFree(bpolicy);
        }

        if(FAILED(hres) || policy != URLPOLICY_ALLOW) {
            IUnknown_Release(obj);
            return NULL;
        }
    }

    hres = set_object_site(ctx, obj);
    if(FAILED(hres)) {
        IUnknown_Release(obj);
        return NULL;
    }

    return obj;
}