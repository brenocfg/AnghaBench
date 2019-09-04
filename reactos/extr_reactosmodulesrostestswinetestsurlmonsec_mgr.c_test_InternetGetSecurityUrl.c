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
typedef  size_t HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 int /*<<< orphan*/  PSU_DEFAULT ; 
 int /*<<< orphan*/  PSU_SECURITY_URL_ONLY ; 
 int /*<<< orphan*/  ParseUrl_SECURITY_DOMAIN_expected ; 
 int /*<<< orphan*/  ParseUrl_SECURITY_URL_expected ; 
 int /*<<< orphan*/  ParseUrl_SECURITY_URL_input2 ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 size_t S_OK ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 size_t pCoInternetGetSecurityUrl (char const*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* security_expectedW ; 
 char const* security_url2W ; 
 int /*<<< orphan*/  strcmp_w (char*,char const*) ; 
 int /*<<< orphan*/  trace (char*) ; 
 char const* url10 ; 
 char const* url2 ; 
 char const* url3 ; 
 char const* url4 ; 
 char const* url5 ; 
 char const* url7 ; 
 char const* url8 ; 
 char const* url9 ; 
 size_t wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_InternetGetSecurityUrl(void)
{
    const WCHAR url5_out[] = {'h','t','t','p',':','w','w','w','.','z','o','n','e','3',
                              '.','w','i','n','e','t','e','s','t',0};
    const WCHAR url7_out[] = {'f','t','p',':','z','o','n','e','3','.','w','i','n','e','t','e','s','t',0};

    const WCHAR *in[] = {url2, url3, url4, url5, url7, url8, url9, url10};
    const WCHAR *out_default[] = {url2, url3, url4, url5_out, url7_out, url8, url5_out, url10};
    const WCHAR *out_securl[] = {url2, url3, url4, url5, url7, url8, url9, url10};

    WCHAR *sec;
    DWORD i;
    HRESULT hres;

    trace("testing CoInternetGetSecurityUrl...\n");

    for(i = 0; i < ARRAY_SIZE(in); i++) {
        hres = pCoInternetGetSecurityUrl(in[i], &sec, PSU_DEFAULT, 0);
        ok(hres == S_OK, "(%d) CoInternetGetSecurityUrl returned: %08x\n", i, hres);
        if(hres == S_OK) {
            ok(!strcmp_w(sec, out_default[i]), "(%d) Got %s, expected %s\n",
                    i, wine_dbgstr_w(sec), wine_dbgstr_w(out_default[i]));
            CoTaskMemFree(sec);
        }

        hres = pCoInternetGetSecurityUrl(in[i], &sec, PSU_SECURITY_URL_ONLY, 0);
        ok(hres == S_OK, "(%d) CoInternetGetSecurityUrl returned: %08x\n", i, hres);
        if(hres == S_OK) {
            ok(!strcmp_w(sec, out_securl[i]), "(%d) Got %s, expected %s\n",
                    i, wine_dbgstr_w(sec), wine_dbgstr_w(out_securl[i]));
            CoTaskMemFree(sec);
        }
    }

    SET_EXPECT(ParseUrl_SECURITY_URL_input2);
    SET_EXPECT(ParseUrl_SECURITY_URL_expected);
    SET_EXPECT(ParseUrl_SECURITY_DOMAIN_expected);

    hres = pCoInternetGetSecurityUrl(security_url2W, &sec, PSU_DEFAULT, 0);
    ok(hres == S_OK, "CoInternetGetSecurityUrl returned 0x%08x, expected S_OK\n", hres);

    CHECK_CALLED(ParseUrl_SECURITY_URL_input2);
    CHECK_CALLED(ParseUrl_SECURITY_URL_expected);
    CHECK_CALLED(ParseUrl_SECURITY_DOMAIN_expected);

    ok(!lstrcmpW(security_expectedW, sec), "Expected %s but got %s\n",
       wine_dbgstr_w(security_expectedW), wine_dbgstr_w(sec));
    CoTaskMemFree(sec);
}