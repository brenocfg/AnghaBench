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
struct TYPE_4__ {int /*<<< orphan*/  uri_url; int /*<<< orphan*/  no_canon_url; int /*<<< orphan*/  uniform_url; int /*<<< orphan*/  legacy_url; int /*<<< orphan*/  uri_flags; int /*<<< orphan*/  base_uri_flags; int /*<<< orphan*/  base_url; int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ create_urlmon_test_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  URL_MK_LEGACY ; 
 int /*<<< orphan*/  URL_MK_NO_CANONICALIZE ; 
 int /*<<< orphan*/  URL_MK_UNIFORM ; 
 int /*<<< orphan*/ * a2w (int /*<<< orphan*/ ) ; 
 TYPE_1__ const* create_urlmon_tests ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateURLMonikerEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateURLMonikerEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateUri (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  test_display_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_urlmon_display_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CreateURLMoniker(void)
{
    const create_urlmon_test_t *test;
    IMoniker *mon, *base_mon;
    WCHAR *url, *base_url;
    IUri *uri, *base_uri;
    HRESULT hres;

    for(test = create_urlmon_tests; test < create_urlmon_tests + ARRAY_SIZE(create_urlmon_tests); test++) {
        url = a2w(test->url);
        base_url = a2w(test->base_url);

        if(base_url) {
            hres = pCreateUri(base_url, test->base_uri_flags, 0, &base_uri);
            ok(hres == S_OK, "CreateUri failed: %08x\n", hres);

            hres = pCreateURLMonikerEx2(NULL, base_uri, &base_mon, URL_MK_NO_CANONICALIZE);
            ok(hres == S_OK, "CreateURLMonikerEx2 failed: %08x\n", hres);
        }else {
            base_uri = NULL;
            base_mon = NULL;
        }

        hres = CreateURLMoniker(base_mon, url, &mon);
        ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);
        test_urlmon_display_name(mon, test->legacy_url);
        test_display_uri(mon, test->legacy_url);
        IMoniker_Release(mon);

        hres = pCreateURLMonikerEx(base_mon, url, &mon, URL_MK_LEGACY);
        ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);
        test_urlmon_display_name(mon, test->legacy_url);
        test_display_uri(mon, test->legacy_url);
        IMoniker_Release(mon);

        hres = pCreateURLMonikerEx(base_mon, url, &mon, URL_MK_UNIFORM);
        ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);
        test_urlmon_display_name(mon, test->uniform_url);
        test_display_uri(mon, test->uniform_url);
        IMoniker_Release(mon);

        hres = pCreateURLMonikerEx(base_mon, url, &mon, URL_MK_NO_CANONICALIZE);
        ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);
        test_urlmon_display_name(mon, test->no_canon_url);
        test_display_uri(mon, test->no_canon_url);
        IMoniker_Release(mon);

        hres = pCreateUri(url, test->uri_flags, 0, &uri);
        ok(hres == S_OK, "CreateUri failed: %08x\n", hres);

        hres = pCreateURLMonikerEx2(base_mon, uri, &mon, URL_MK_LEGACY);
        ok(hres == S_OK, "CreateURLMonikerEx2 failed: %08x\n", hres);
        test_urlmon_display_name(mon, base_url ? test->legacy_url : test->uri_url);
        test_display_uri(mon, base_url ? test->legacy_url : test->uri_url);
        IMoniker_Release(mon);

        hres = pCreateURLMonikerEx2(base_mon, uri, &mon, URL_MK_UNIFORM);
        ok(hres == S_OK, "CreateURLMonikerEx2 failed: %08x\n", hres);
        test_urlmon_display_name(mon, base_url ? test->uniform_url : test->uri_url);
        test_display_uri(mon, base_url ? test->uniform_url : test->uri_url);
        IMoniker_Release(mon);

        hres = pCreateURLMonikerEx2(base_mon, uri, &mon, URL_MK_NO_CANONICALIZE);
        ok(hres == S_OK, "CreateURLMonikerEx2 failed: %08x\n", hres);
        test_urlmon_display_name(mon, base_url ? test->no_canon_url : test->uri_url);
        test_display_uri(mon, base_url ? test->no_canon_url : test->uri_url);
        IMoniker_Release(mon);

        IUri_Release(uri);
        heap_free(url);
        heap_free(base_url);
        if(base_uri)
            IUri_Release(base_uri);
        if(base_mon)
            IMoniker_Release(base_mon);
    }
}