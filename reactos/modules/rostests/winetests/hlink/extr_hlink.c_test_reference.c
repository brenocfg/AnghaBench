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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHlink ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int E_NOTIMPL ; 
 scalar_t__ FAILED (int) ; 
 int HLINKGETREF_DEFAULT ; 
 int HlinkCreateFromString (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IHlink_GetAdditionalParams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IHlink_GetMonikerReference (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int IHlink_GetStringReference (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHlink_Release (int /*<<< orphan*/ *) ; 
 int IHlink_SetAdditionalParams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHlink ; 
 int IMoniker_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_reference(void)
{
    HRESULT r;
    IHlink *lnk = NULL;
    IMoniker *mk = NULL;
    const WCHAR url[] = { 'h','t','t','p',':','/','/','w','i','n','e','h','q','.','o','r','g',0 };
    const WCHAR url2[] = { 'h','t','t','p',':','/','/','w','i','n','e','h','q','.','o','r','g','/',0 };
    LPWSTR str = NULL;

    r = HlinkCreateFromString(url, NULL, NULL, NULL,
                              0, NULL, &IID_IHlink, (LPVOID*) &lnk);
    ok(r == S_OK, "failed to create link\n");
    if (FAILED(r))
        return;

    r = IHlink_GetMonikerReference(lnk, HLINKGETREF_DEFAULT, NULL, NULL);
    ok(r == S_OK, "failed\n");

    r = IHlink_GetMonikerReference(lnk, HLINKGETREF_DEFAULT, &mk, &str);
    ok(r == S_OK, "failed\n");
    ok(mk != NULL, "no moniker\n");
    ok(str == NULL, "string should be null\n");

    r = IMoniker_Release(mk);
    ok( r == 1, "moniker refcount wrong\n");

    r = IHlink_GetStringReference(lnk, -1, &str, NULL);
    ok(r == S_OK, "failed\n");
    CoTaskMemFree(str);

    r = IHlink_GetStringReference(lnk, -1, NULL, NULL);
    ok(r == S_OK, "failed, r=%08x\n", r);

    r = IHlink_GetStringReference(lnk, -1, NULL, &str);
    ok(r == S_OK, "failed, r=%08x\n", r);
    ok(str == NULL, "string should be null\n");

    r = IHlink_GetStringReference(lnk, HLINKGETREF_DEFAULT, &str, NULL);
    ok(r == S_OK, "failed\n");
    ok(!lstrcmpW(str, url2), "url wrong\n");
    CoTaskMemFree(str);

    r = IHlink_GetStringReference(lnk, HLINKGETREF_DEFAULT, NULL, NULL);
    ok(r == S_OK, "failed\n");

    r = IHlink_GetStringReference(lnk, HLINKGETREF_DEFAULT, NULL, &str);
    ok(r == S_OK, "failed\n");
    ok(str == NULL, "string should be null\n");

    /* Unimplented functions checks */
    r = IHlink_GetAdditionalParams(lnk, NULL);
    ok(r == E_NOTIMPL, "failed\n");

    r = IHlink_SetAdditionalParams(lnk, NULL);
    ok(r == E_NOTIMPL, "failed\n");

    IHlink_Release(lnk);
}