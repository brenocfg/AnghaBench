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
struct TYPE_3__ {int /*<<< orphan*/ * cf; int /*<<< orphan*/  urlmon; } ;
typedef  TYPE_1__ name_space ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IInternetProtocolInfo ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInternetParseUrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IClassFactory_CreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IInternetProtocolInfo ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_SCHEMA ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_name_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_protocol_cf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  session_cs ; 

IInternetProtocolInfo *get_protocol_info(LPCWSTR url)
{
    IInternetProtocolInfo *ret = NULL;
    IClassFactory *cf;
    name_space *ns;
    WCHAR schema[64];
    DWORD schema_len;
    HRESULT hres;

    hres = CoInternetParseUrl(url, PARSE_SCHEMA, 0, schema, ARRAY_SIZE(schema), &schema_len, 0);
    if(FAILED(hres) || !schema_len)
        return NULL;

    EnterCriticalSection(&session_cs);

    ns = find_name_space(schema);
    if(ns && !ns->urlmon) {
        hres = IClassFactory_QueryInterface(ns->cf, &IID_IInternetProtocolInfo, (void**)&ret);
        if(FAILED(hres))
            hres = IClassFactory_CreateInstance(ns->cf, NULL, &IID_IInternetProtocolInfo, (void**)&ret);
    }

    LeaveCriticalSection(&session_cs);

    if(ns && SUCCEEDED(hres))
        return ret;

    hres = get_protocol_cf(schema, schema_len, NULL, &cf);
    if(FAILED(hres))
        return NULL;

    hres = IClassFactory_QueryInterface(cf, &IID_IInternetProtocolInfo, (void**)&ret);
    if(FAILED(hres))
        IClassFactory_CreateInstance(cf, NULL, &IID_IInternetProtocolInfo, (void**)&ret);
    IClassFactory_Release(cf);

    return ret;
}