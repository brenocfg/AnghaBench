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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 scalar_t__ PathIsURLW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int URL_APPLY_DEFAULT ; 
 int URL_APPLY_GUESSFILE ; 
 int URL_APPLY_GUESSSCHEME ; 
 int /*<<< orphan*/  UrlApplySchemeW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_moniker(LPCWSTR url, IMoniker **mon)
{
    WCHAR new_url[INTERNET_MAX_URL_LENGTH];
    DWORD size;
    HRESULT hres;

    if(PathIsURLW(url))
        return CreateURLMoniker(NULL, url, mon);

    size = ARRAY_SIZE(new_url);
    hres = UrlApplySchemeW(url, new_url, &size, URL_APPLY_GUESSSCHEME | URL_APPLY_GUESSFILE | URL_APPLY_DEFAULT);
    TRACE("was %s got %s\n", debugstr_w(url), debugstr_w(new_url));
    if(FAILED(hres)) {
        WARN("UrlApplyScheme failed: %08x\n", hres);
        return hres;
    }

    return CreateURLMoniker(NULL, new_url, mon);
}