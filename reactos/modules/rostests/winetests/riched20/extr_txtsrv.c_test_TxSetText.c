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
typedef  int /*<<< orphan*/  ITextServices ;
typedef  int /*<<< orphan*/  ITextHost ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextServices_Release (int /*<<< orphan*/ *) ; 
 int ITextServices_TxGetText (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ITextServices_TxSetText (int /*<<< orphan*/ *,char*) ; 
 int S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysStringByteLen (int /*<<< orphan*/ ) ; 
 int SysStringLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_texthost (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_TxSetText(void)
{
    ITextServices *txtserv;
    ITextHost *host;
    HRESULT hres;
    BSTR rettext;
    WCHAR settext[] = {'T','e','s','t',0};

    if (!init_texthost(&txtserv, &host))
        return;

    hres = ITextServices_TxSetText(txtserv, settext);
    ok(hres == S_OK, "ITextServices_TxSetText failed (result = %x)\n", hres);

    hres = ITextServices_TxGetText(txtserv, &rettext);
    ok(hres == S_OK, "ITextServices_TxGetText failed (result = %x)\n", hres);

    ok(SysStringLen(rettext) == 4,
                 "String returned of wrong length (expected 4, got %d)\n", SysStringLen(rettext));
    ok(memcmp(rettext,settext,SysStringByteLen(rettext)) == 0,
                 "String returned differs\n");

    /* Null-pointer should behave the same as empty-string */

    hres = ITextServices_TxSetText(txtserv, 0);
    ok(hres == S_OK, "ITextServices_TxSetText failed (result = %x)\n", hres);

    hres = ITextServices_TxGetText(txtserv, &rettext);
    ok(hres == S_OK, "ITextServices_TxGetText failed (result = %x)\n", hres);
    ok(SysStringLen(rettext) == 0,
                 "String returned of wrong length (expected 0, got %d)\n", SysStringLen(rettext));

    SysFreeString(rettext);
    ITextServices_Release(txtserv);
    ITextHost_Release(host);
}