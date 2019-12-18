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
typedef  int /*<<< orphan*/  ITextServices ;
typedef  int /*<<< orphan*/  ITextHost ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ITextHost_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextServices_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextServices_TxGetText (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_texthost (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_TxGetText(void)
{
    ITextServices *txtserv;
    ITextHost *host;
    HRESULT hres;
    BSTR rettext;

    if (!init_texthost(&txtserv, &host))
        return;

    hres = ITextServices_TxGetText(txtserv, &rettext);
    ok(hres == S_OK, "ITextServices_TxGetText failed (result = %x)\n", hres);
    SysFreeString(rettext);

    ITextServices_Release(txtserv);
    ITextHost_Release(host);
}