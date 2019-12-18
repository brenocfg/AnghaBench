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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  IHtmlLoadOptions ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_HTMLLoadOptions ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int HTMLLOADOPTION_CODEPAGE ; 
 scalar_t__ HTMLLOADOPTION_FRAMELOAD ; 
 scalar_t__ IHtmlLoadOptions_QueryOption (int /*<<< orphan*/ *,int,int*,scalar_t__*) ; 
 int /*<<< orphan*/  IHtmlLoadOptions_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHtmlLoadOptions_SetOption (int /*<<< orphan*/ *,int,...) ; 
 int /*<<< orphan*/  IID_IHtmlLoadOptions ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_HTMLLoadOptions(void)
{
    IHtmlLoadOptions *loadopts;
    BYTE buf[100];
    DWORD size, i, data = 0xdeadbeef;
    HRESULT hres;

    hres = CoCreateInstance(&CLSID_HTMLLoadOptions, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IHtmlLoadOptions, (void**)&loadopts);
    ok(hres == S_OK, "creating HTMLLoadOptions failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    for(i=0; i <= HTMLLOADOPTION_FRAMELOAD+3; i++) {
        size = 0xdeadbeef;
        memset(buf, 0xdd, sizeof(buf));
        hres = IHtmlLoadOptions_QueryOption(loadopts, i, NULL, &size);
        ok(hres == S_OK, "QueryOption failed: %08x\n", hres);
        ok(size == 0, "size = %d\n", size);
        ok(buf[0] == 0xdd, "buf changed\n");
    }

    size = 0xdeadbeef;
    hres = IHtmlLoadOptions_QueryOption(loadopts, HTMLLOADOPTION_CODEPAGE, NULL, &size);
    ok(hres == S_OK, "QueryOption failed: %08x\n", hres);
    ok(size == 0, "size = %d\n", size);

    hres = IHtmlLoadOptions_SetOption(loadopts, HTMLLOADOPTION_CODEPAGE, &data, sizeof(data));
    ok(hres == S_OK, "SetOption failed: %08x\n", hres);

    size = sizeof(data);
    memset(buf, 0xdd, sizeof(buf));
    hres = IHtmlLoadOptions_QueryOption(loadopts, HTMLLOADOPTION_CODEPAGE, buf, &size);
    ok(hres == S_OK, "QueryOption failed: %08x\n", hres);
    ok(size == sizeof(data), "size = %d\n", size);
    ok(*(DWORD*)buf == data, "unexpected buf\n");

    size = sizeof(data)-1;
    memset(buf, 0xdd, sizeof(buf));
    hres = IHtmlLoadOptions_QueryOption(loadopts, HTMLLOADOPTION_CODEPAGE, buf, &size);
    ok(hres == E_FAIL, "QueryOption failed: %08x\n", hres);
    ok(size == sizeof(data) || !size, "size = %d\n", size);
    ok(buf[0] == 0xdd, "buf changed\n");

    data = 100;
    hres = IHtmlLoadOptions_SetOption(loadopts, HTMLLOADOPTION_CODEPAGE, &data, 0);
    ok(hres == S_OK, "SetOption failed: %08x\n", hres);

    size = 0xdeadbeef; 
    memset(buf, 0xdd, sizeof(buf));
    hres = IHtmlLoadOptions_QueryOption(loadopts, HTMLLOADOPTION_CODEPAGE, buf, &size);
    ok(hres == S_OK, "QueryOption failed: %08x\n", hres);
    ok(size == 0, "size = %d\n", size);
    ok(buf[0] == 0xdd, "buf changed\n");

    hres = IHtmlLoadOptions_SetOption(loadopts, HTMLLOADOPTION_CODEPAGE, NULL, 0);
    ok(hres == S_OK, "SetOption failed: %08x\n", hres);

    hres = IHtmlLoadOptions_SetOption(loadopts, 1000, &data, sizeof(data));
    ok(hres == S_OK, "SetOption failed: %08x\n", hres);

    size = sizeof(data);
    memset(buf, 0xdd, sizeof(buf));
    hres = IHtmlLoadOptions_QueryOption(loadopts, 1000, buf, &size);
    ok(hres == S_OK, "QueryOption failed: %08x\n", hres);
    ok(size == sizeof(data), "size = %d\n", size);
    ok(*(DWORD*)buf == data, "unexpected buf\n");

    hres = IHtmlLoadOptions_SetOption(loadopts, 1000, buf, sizeof(buf));
    ok(hres == S_OK, "SetOption failed: %08x\n", hres);

    size = 0xdeadbeef;
    hres = IHtmlLoadOptions_QueryOption(loadopts, 1000, buf, &size);
    ok(hres == S_OK, "QueryOption failed: %08x\n", hres);
    ok(size == sizeof(buf), "size = %d\n", size);

    IHtmlLoadOptions_Release(loadopts);
}