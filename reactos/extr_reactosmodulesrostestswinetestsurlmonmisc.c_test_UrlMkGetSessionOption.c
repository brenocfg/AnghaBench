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
typedef  int /*<<< orphan*/  encoding ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int S_OK ; 
 int /*<<< orphan*/  URLMON_OPTION_URL_ENCODING ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pUrlMkGetSessionOption (int /*<<< orphan*/ ,int*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_UrlMkGetSessionOption(void)
{
    DWORD encoding, size;
    HRESULT hres;

    size = encoding = 0xdeadbeef;
    hres = pUrlMkGetSessionOption(URLMON_OPTION_URL_ENCODING, &encoding,
                                 sizeof(encoding), &size, 0);
    ok(hres == S_OK, "UrlMkGetSessionOption failed: %08x\n", hres);
    ok(encoding != 0xdeadbeef, "encoding not changed\n");
    ok(size == sizeof(encoding), "size=%d\n", size);

    size = encoding = 0xdeadbeef;
    hres = pUrlMkGetSessionOption(URLMON_OPTION_URL_ENCODING, &encoding,
                                 sizeof(encoding)+1, &size, 0);
    ok(hres == S_OK, "UrlMkGetSessionOption failed: %08x\n", hres);
    ok(encoding != 0xdeadbeef, "encoding not changed\n");
    ok(size == sizeof(encoding), "size=%d\n", size);

    size = encoding = 0xdeadbeef;
    hres = pUrlMkGetSessionOption(URLMON_OPTION_URL_ENCODING, &encoding,
                                 sizeof(encoding)-1, &size, 0);
    ok(hres == E_INVALIDARG, "UrlMkGetSessionOption failed: %08x\n", hres);
    ok(encoding == 0xdeadbeef, "encoding = %08x, exepcted 0xdeadbeef\n", encoding);
    ok(size == 0xdeadbeef, "size=%d\n", size);

    size = encoding = 0xdeadbeef;
    hres = pUrlMkGetSessionOption(URLMON_OPTION_URL_ENCODING, NULL,
                                 sizeof(encoding)-1, &size, 0);
    ok(hres == E_INVALIDARG, "UrlMkGetSessionOption failed: %08x\n", hres);
    ok(encoding == 0xdeadbeef, "encoding = %08x, exepcted 0xdeadbeef\n", encoding);
    ok(size == 0xdeadbeef, "size=%d\n", size);

    encoding = 0xdeadbeef;
    hres = pUrlMkGetSessionOption(URLMON_OPTION_URL_ENCODING, &encoding,
                                 sizeof(encoding)-1, NULL, 0);
    ok(hres == E_INVALIDARG, "UrlMkGetSessionOption failed: %08x\n", hres);
    ok(encoding == 0xdeadbeef, "encoding = %08x, exepcted 0xdeadbeef\n", encoding);
}