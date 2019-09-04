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
struct TYPE_3__ {int /*<<< orphan*/ * secmgr; int /*<<< orphan*/  site; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  IInternetHostSecurityManager ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptSite_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IInternetHostSecurityManager ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IServiceProvider_QueryService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SID_SInternetHostSecurityManager ; 

__attribute__((used)) static IInternetHostSecurityManager *get_sec_mgr(script_ctx_t *ctx)
{
    IInternetHostSecurityManager *secmgr;
    IServiceProvider *sp;
    HRESULT hres;

    if(!ctx->site)
        return NULL;

    if(ctx->secmgr)
        return ctx->secmgr;

    hres = IActiveScriptSite_QueryInterface(ctx->site, &IID_IServiceProvider, (void**)&sp);
    if(FAILED(hres))
        return NULL;

    hres = IServiceProvider_QueryService(sp, &SID_SInternetHostSecurityManager, &IID_IInternetHostSecurityManager,
            (void**)&secmgr);
    IServiceProvider_Release(sp);
    if(FAILED(hres))
        return NULL;

    return ctx->secmgr = secmgr;
}