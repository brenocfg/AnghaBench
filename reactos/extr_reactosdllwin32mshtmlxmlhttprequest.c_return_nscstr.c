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
typedef  int /*<<< orphan*/  nsACString ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nsACString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsACString_GetData (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static HRESULT return_nscstr(nsresult nsres, nsACString *nscstr, BSTR *p)
{
    const char *str;
    int len;

    if(NS_FAILED(nsres)) {
        ERR("failed: %08x\n", nsres);
        nsACString_Finish(nscstr);
        return E_FAIL;
    }

    nsACString_GetData(nscstr, &str);

    if(*str) {
        len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
        *p = SysAllocStringLen(NULL, len);
        if(!*p) {
            nsACString_Finish(nscstr);
            return E_OUTOFMEMORY;
        }
        MultiByteToWideChar(CP_UTF8, 0, str, -1, *p, len);
    }else {
        *p = NULL;
    }

    nsACString_Finish(nscstr);
    return S_OK;
}