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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  URL_COMPONENTSW ;
typedef  int /*<<< orphan*/  HTMLLocation ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  InternetCrackUrlW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_url (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT get_url_components(HTMLLocation *This, URL_COMPONENTSW *url)
{
    const WCHAR *doc_url;
    HRESULT hres;

    hres = get_url(This, &doc_url);
    if(FAILED(hres))
        return hres;

    if(!InternetCrackUrlW(doc_url, 0, 0, url)) {
        FIXME("InternetCrackUrlW failed: 0x%08x\n", GetLastError());
        SetLastError(0);
        return E_FAIL;
    }

    return S_OK;
}