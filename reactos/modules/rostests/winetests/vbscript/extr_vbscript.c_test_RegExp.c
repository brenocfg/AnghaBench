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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ISubMatches ;
typedef  int /*<<< orphan*/  IRegExp2 ;
typedef  int /*<<< orphan*/  IMatchCollection2 ;
typedef  int /*<<< orphan*/  IMatch2 ;
typedef  int /*<<< orphan*/  IEnumVARIANT ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_VBScriptRegExp ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int E_POINTER ; 
 int IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IEnumVARIANT_Release (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IEnumVARIANT ; 
 int /*<<< orphan*/  IID_IMatch ; 
 int /*<<< orphan*/  IID_IMatch2 ; 
 int /*<<< orphan*/  IID_IMatchCollection ; 
 int /*<<< orphan*/  IID_IMatchCollection2 ; 
 int /*<<< orphan*/  IID_IRegExp ; 
 int /*<<< orphan*/  IID_IRegExp2 ; 
 int /*<<< orphan*/  IID_ISubMatches ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IMatch2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMatch2_Release (int /*<<< orphan*/ *) ; 
 int IMatch2_get_FirstIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IMatch2_get_Length (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IMatch2_get_SubMatches (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IMatch2_get_Value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IMatchCollection2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMatchCollection2_Release (int /*<<< orphan*/ *) ; 
 int IMatchCollection2_get_Count (int /*<<< orphan*/ *,int*) ; 
 int IMatchCollection2_get_Item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int IMatchCollection2_get__NewEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IRegExp2_Execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IRegExp2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IRegExp2_Release (int /*<<< orphan*/ *) ; 
 int IRegExp2_get_Global (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IRegExp2_get_IgnoreCase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IRegExp2_get_Pattern (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ISubMatches_Release (int /*<<< orphan*/ *) ; 
 int ISubMatches_get_Count (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ISubMatches_get_Item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int REGDB_E_CLASSNOTREG ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RegExp(void)
{
    IRegExp2 *regexp;
    IMatchCollection2 *mc;
    IMatch2 *match;
    ISubMatches *sm;
    IEnumVARIANT *ev;
    IUnknown *unk;
    IDispatch *disp;
    HRESULT hres;
    BSTR bstr;
    LONG count;
    VARIANT v;
    ULONG fetched;

    hres = CoCreateInstance(&CLSID_VBScriptRegExp, NULL,
            CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IUnknown, (void**)&unk);
    if(hres == REGDB_E_CLASSNOTREG) {
        win_skip("VBScriptRegExp is not registered\n");
        return;
    }
    ok(hres == S_OK, "CoCreateInstance(CLSID_VBScriptRegExp) failed: %x\n", hres);

    hres = IUnknown_QueryInterface(unk, &IID_IRegExp2, (void**)&regexp);
    if(hres == E_NOINTERFACE) {
        win_skip("IRegExp2 interface is not available\n");
        return;
    }
    ok(hres == S_OK, "QueryInterface(IID_IRegExp2) failed: %x\n", hres);
    IUnknown_Release(unk);

    hres = IRegExp2_QueryInterface(regexp, &IID_IRegExp, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IRegExp) returned %x\n", hres);
    IUnknown_Release(unk);

    hres = IRegExp2_QueryInterface(regexp, &IID_IDispatchEx, (void**)&unk);
    ok(hres == E_NOINTERFACE, "QueryInterface(IID_IDispatchEx) returned %x\n", hres);

    hres = IRegExp2_get_Pattern(regexp, &bstr);
    ok(bstr == NULL, "bstr != NULL\n");
    ok(hres == S_OK, "get_Pattern returned %x, expected S_OK\n", hres);

    hres = IRegExp2_get_Pattern(regexp, NULL);
    ok(hres == E_POINTER, "get_Pattern returned %x, expected E_POINTER\n", hres);

    hres = IRegExp2_get_IgnoreCase(regexp, NULL);
    ok(hres == E_POINTER, "get_IgnoreCase returned %x, expected E_POINTER\n", hres);

    hres = IRegExp2_get_Global(regexp, NULL);
    ok(hres == E_POINTER, "get_Global returned %x, expected E_POINTER\n", hres);

    hres = IRegExp2_Execute(regexp, NULL, &disp);
    ok(hres == S_OK, "Execute returned %x, expected S_OK\n", hres);
    hres = IDispatch_QueryInterface(disp, &IID_IMatchCollection2, (void**)&mc);
    ok(hres == S_OK, "QueryInterface(IID_IMatchCollection2) returned %x\n", hres);
    IDispatch_Release(disp);

    hres = IMatchCollection2_QueryInterface(mc, &IID_IMatchCollection, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IMatchCollection) returned %x\n", hres);
    IUnknown_Release(unk);

    hres = IMatchCollection2_get_Count(mc, NULL);
    ok(hres == E_POINTER, "get_Count returned %x, expected E_POINTER\n", hres);

    hres = IMatchCollection2_get_Count(mc, &count);
    ok(hres == S_OK, "get_Count returned %x, expected S_OK\n", hres);
    ok(count == 1, "count = %d\n", count);

    hres = IMatchCollection2_get_Item(mc, 1, &disp);
    ok(hres == E_INVALIDARG, "get_Item returned %x, expected E_INVALIDARG\n", hres);

    hres = IMatchCollection2_get_Item(mc, 1, NULL);
    ok(hres == E_POINTER, "get_Item returned %x, expected E_POINTER\n", hres);

    hres = IMatchCollection2_get_Item(mc, 0, &disp);
    ok(hres == S_OK, "get_Item returned %x, expected S_OK\n", hres);
    hres = IDispatch_QueryInterface(disp, &IID_IMatch2, (void**)&match);
    ok(hres == S_OK, "QueryInterface(IID_IMatch2) returned %x\n", hres);
    IDispatch_Release(disp);

    hres = IMatch2_QueryInterface(match, &IID_IMatch, (void**)&unk);
    ok(hres == S_OK, "QueryInterface(IID_IMatch) returned %x\n", hres);
    IUnknown_Release(unk);

    hres = IMatch2_get_Value(match, NULL);
    ok(hres == E_POINTER, "get_Value returned %x, expected E_POINTER\n", hres);

    hres = IMatch2_get_FirstIndex(match, NULL);
    ok(hres == E_POINTER, "get_FirstIndex returned %x, expected E_POINTER\n", hres);

    hres = IMatch2_get_Length(match, NULL);
    ok(hres == E_POINTER, "get_Length returned %x, expected E_POINTER\n", hres);

    hres = IMatch2_get_SubMatches(match, NULL);
    ok(hres == E_POINTER, "get_SubMatches returned %x, expected E_POINTER\n", hres);

    hres = IMatch2_get_SubMatches(match, &disp);
    ok(hres == S_OK, "get_SubMatches returned %x, expected S_OK\n", hres);
    IMatch2_Release(match);
    hres = IDispatch_QueryInterface(disp, &IID_ISubMatches, (void**)&sm);
    ok(hres == S_OK, "QueryInterface(IID_ISubMatches) returned %x\n", hres);
    IDispatch_Release(disp);

    hres = ISubMatches_get_Item(sm, 0, &v);
    ok(hres == E_INVALIDARG, "get_Item returned %x, expected E_INVALIDARG\n", hres);

    hres = ISubMatches_get_Item(sm, 0, NULL);
    ok(hres == E_POINTER, "get_Item returned %x, expected E_POINTER\n", hres);

    hres = ISubMatches_get_Count(sm, NULL);
    ok(hres == E_POINTER, "get_Count returned %x, expected E_POINTER\n", hres);
    ISubMatches_Release(sm);

    hres = IMatchCollection2_get__NewEnum(mc, &unk);
    ok(hres == S_OK, "get__NewEnum returned %x, expected S_OK\n", hres);
    hres = IUnknown_QueryInterface(unk, &IID_IEnumVARIANT, (void**)&ev);
    ok(hres == S_OK, "QueryInterface(IID_IEnumVARIANT) returned %x\n", hres);
    IUnknown_Release(unk);
    IMatchCollection2_Release(mc);

    hres = IEnumVARIANT_Skip(ev, 2);
    ok(hres == S_OK, "Skip returned %x\n", hres);

    hres = IEnumVARIANT_Next(ev, 1, &v, &fetched);
    ok(hres == S_FALSE, "Next returned %x, expected S_FALSE\n", hres);
    ok(fetched == 0, "fetched = %d\n", fetched);

    hres = IEnumVARIANT_Skip(ev, -1);
    ok(hres == S_OK, "Skip returned %x\n", hres);

    hres = IEnumVARIANT_Next(ev, 1, &v, &fetched);
    ok(hres == S_OK, "Next returned %x\n", hres);
    ok(fetched == 1, "fetched = %d\n", fetched);
    VariantClear(&v);
    IEnumVARIANT_Release(ev);

    IRegExp2_Release(regexp);
}