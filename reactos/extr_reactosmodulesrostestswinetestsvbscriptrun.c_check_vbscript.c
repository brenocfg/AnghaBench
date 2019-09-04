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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRegExp2 ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_VBScriptRegExp ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int FALSE ; 
 int /*<<< orphan*/  IID_IRegExp2 ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IRegExp2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static BOOL check_vbscript(void)
{
    IRegExp2 *regexp;
    IUnknown *unk;
    HRESULT hres;

    hres = CoCreateInstance(&CLSID_VBScriptRegExp, NULL,
            CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IUnknown, (void**)&unk);
    if(hres == REGDB_E_CLASSNOTREG)
        return FALSE;
    ok(hres == S_OK, "CoCreateInstance(CLSID_VBScriptRegExp) failed: %x\n", hres);

    hres = IUnknown_QueryInterface(unk, &IID_IRegExp2, (void**)&regexp);
    if(SUCCEEDED(hres))
        IRegExp2_Release(regexp);
    IUnknown_Release(unk);

    return hres == S_OK;
}