#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  float WCHAR ;
struct TYPE_24__ {void* vt; } ;
struct TYPE_25__ {TYPE_3__ tdesc; } ;
struct TYPE_30__ {int memid; int funckind; int invkind; int callconv; int cParams; int oVft; int wFuncFlags; TYPE_4__ elemdescFunc; TYPE_11__* lprgelemdescParam; } ;
struct TYPE_29__ {int /*<<< orphan*/  cMembers; TYPE_7__* pmethdata; } ;
struct TYPE_28__ {int dispid; int iMeth; int cc; int cArgs; int wFlags; void* szName; void* vtReturn; TYPE_6__* ppdata; } ;
struct TYPE_27__ {int vt; void* szName; } ;
struct TYPE_21__ {int Data1; } ;
struct TYPE_26__ {int typekind; int cImplTypes; int cFuncs; int wTypeFlags; TYPE_12__ guid; } ;
struct TYPE_23__ {int wParamFlags; } ;
struct TYPE_22__ {void* vt; } ;
struct TYPE_20__ {TYPE_1__ tdesc; } ;
struct TYPE_19__ {TYPE_2__ paramdesc; } ;
typedef  TYPE_5__ TYPEATTR ;
typedef  TYPE_6__ PARAMDATA ;
typedef  float OLECHAR ;
typedef  TYPE_7__ METHODDATA ;
typedef  int MEMBERID ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  TYPE_8__ INTERFACEDATA ;
typedef  int HRESULT ;
typedef  int HREFTYPE ;
typedef  TYPE_9__ FUNCDESC ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_7__*) ; 
 void* CC_STDCALL ; 
 int CreateDispTypeInfo (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int DISPATCH_METHOD ; 
 void* DISPATCH_PROPERTYGET ; 
 int DISPATCH_PROPERTYPUT ; 
 int FUNC_VIRTUAL ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int ITypeInfo_GetFuncDesc (int /*<<< orphan*/ *,int,TYPE_9__**) ; 
 int ITypeInfo_GetIDsOfNames (int /*<<< orphan*/ *,float**,int,int*) ; 
 int ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseFuncDesc (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int IsEqualGUID (TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int PARAMFLAG_NONE ; 
 int S_OK ; 
 void* SysAllocString (float const*) ; 
 int /*<<< orphan*/  SysFreeString (void*) ; 
 int TKIND_COCLASS ; 
 int TKIND_INTERFACE ; 
 TYPE_10__ U (TYPE_11__) ; 
 int VT_BSTR ; 
 void* VT_HRESULT ; 
 void* VT_I4 ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_CreateDispTypeInfo(void)
{
    ITypeInfo *pTypeInfo, *pTI2;
    HRESULT hr;
    INTERFACEDATA ifdata;
    METHODDATA methdata[4];
    PARAMDATA parms1[2];
    PARAMDATA parms3[1];
    TYPEATTR *pTypeAttr;
    HREFTYPE href;
    FUNCDESC *pFuncDesc;
    MEMBERID memid;

    static WCHAR func1[] = {'f','u','n','c','1',0};
    static const WCHAR func2[] = {'f','u','n','c','2',0};
    static const WCHAR func3[] = {'f','u','n','c','3',0};
    static const WCHAR parm1[] = {'p','a','r','m','1',0};
    static const WCHAR parm2[] = {'p','a','r','m','2',0};
    OLECHAR *name = func1;

    ifdata.pmethdata = methdata;
    ifdata.cMembers = ARRAY_SIZE(methdata);

    methdata[0].szName = SysAllocString(func1);
    methdata[0].ppdata = parms1;
    methdata[0].dispid = 0x123;
    methdata[0].iMeth = 0;
    methdata[0].cc = CC_STDCALL;
    methdata[0].cArgs = 2;
    methdata[0].wFlags = DISPATCH_METHOD;
    methdata[0].vtReturn = VT_HRESULT;
    parms1[0].szName = SysAllocString(parm1);
    parms1[0].vt = VT_I4;
    parms1[1].szName = SysAllocString(parm2);
    parms1[1].vt = VT_BSTR;

    methdata[1].szName = SysAllocString(func2);
    methdata[1].ppdata = NULL;
    methdata[1].dispid = 0x124;
    methdata[1].iMeth = 1;
    methdata[1].cc = CC_STDCALL;
    methdata[1].cArgs = 0;
    methdata[1].wFlags = DISPATCH_PROPERTYGET;
    methdata[1].vtReturn = VT_I4;

    methdata[2].szName = SysAllocString(func3);
    methdata[2].ppdata = parms3;
    methdata[2].dispid = 0x125;
    methdata[2].iMeth = 3;
    methdata[2].cc = CC_STDCALL;
    methdata[2].cArgs = 1;
    methdata[2].wFlags = DISPATCH_PROPERTYPUT;
    methdata[2].vtReturn = VT_HRESULT;
    parms3[0].szName = SysAllocString(parm1);
    parms3[0].vt = VT_I4;

    methdata[3].szName = SysAllocString(func3);
    methdata[3].ppdata = NULL;
    methdata[3].dispid = 0x125;
    methdata[3].iMeth = 4;
    methdata[3].cc = CC_STDCALL;
    methdata[3].cArgs = 0;
    methdata[3].wFlags = DISPATCH_PROPERTYGET;
    methdata[3].vtReturn = VT_I4;

    hr = CreateDispTypeInfo(&ifdata, LOCALE_NEUTRAL, &pTypeInfo);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTypeInfo, &pTypeAttr);
    ok(hr == S_OK, "hr %08x\n", hr);

    ok(pTypeAttr->typekind == TKIND_COCLASS, "typekind %0x\n", pTypeAttr->typekind);
    ok(pTypeAttr->cImplTypes == 1, "cImplTypes %d\n", pTypeAttr->cImplTypes);
    ok(pTypeAttr->cFuncs == 0, "cFuncs %d\n", pTypeAttr->cFuncs);
    ok(pTypeAttr->wTypeFlags == 0, "wTypeFlags %04x\n", pTypeAttr->cFuncs);
    ITypeInfo_ReleaseTypeAttr(pTypeInfo, pTypeAttr);

    hr = ITypeInfo_GetRefTypeOfImplType(pTypeInfo, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(href == 0, "href = 0x%x\n", href);
    hr = ITypeInfo_GetRefTypeInfo(pTypeInfo, href, &pTI2);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI2, &pTypeAttr);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTypeAttr->typekind == TKIND_INTERFACE, "typekind %0x\n", pTypeAttr->typekind);
    ok(pTypeAttr->cFuncs == 4, "cFuncs %d\n", pTypeAttr->cFuncs);
    ok(IsEqualGUID(&pTypeAttr->guid, &GUID_NULL), "guid {%08x-...}\n", pTypeAttr->guid.Data1);
    ok(pTypeAttr->wTypeFlags == 0, "typeflags %08x\n", pTypeAttr->wTypeFlags);

    ITypeInfo_ReleaseTypeAttr(pTI2, pTypeAttr);

    hr = ITypeInfo_GetFuncDesc(pTI2, 0, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->memid == 0x123, "memid %x\n", pFuncDesc->memid);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[0].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[0].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[0].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 0, "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_HRESULT, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ok(pFuncDesc->lprgelemdescParam[0].tdesc.vt == VT_I4, "parm 0 vt %x\n", pFuncDesc->lprgelemdescParam[0].tdesc.vt);
    ok(U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags == PARAMFLAG_NONE, "parm 0 flags %x\n", U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags);

    ok(pFuncDesc->lprgelemdescParam[1].tdesc.vt == VT_BSTR, "parm 1 vt %x\n", pFuncDesc->lprgelemdescParam[1].tdesc.vt);
    ok(U(pFuncDesc->lprgelemdescParam[1]).paramdesc.wParamFlags == PARAMFLAG_NONE, "parm 1 flags %x\n", U(pFuncDesc->lprgelemdescParam[1]).paramdesc.wParamFlags);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    hr = ITypeInfo_GetFuncDesc(pTI2, 1, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[1].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[1].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[1].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == sizeof(void *), "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_I4, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    hr = ITypeInfo_GetFuncDesc(pTI2, 2, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[2].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[2].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[2].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 3 * sizeof(void *), "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_HRESULT, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ok(pFuncDesc->lprgelemdescParam[0].tdesc.vt == VT_I4, "parm 0 vt %x\n", pFuncDesc->lprgelemdescParam[0].tdesc.vt);
    ok(U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags == PARAMFLAG_NONE, "parm 0 flags %x\n", U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    hr = ITypeInfo_GetFuncDesc(pTI2, 3, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[3].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[3].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[3].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 4 * sizeof(void *), "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_I4, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    /* test GetIDsOfNames on a coclass to see if it searches its interfaces */
    hr = ITypeInfo_GetIDsOfNames(pTypeInfo, &name, 1, &memid);
    ok(hr == S_OK, "hr 0x%08x\n", hr);
    ok(memid == 0x123, "memid 0x%08x\n", memid);

    ITypeInfo_Release(pTI2);
    ITypeInfo_Release(pTypeInfo);

    SysFreeString(parms1[0].szName);
    SysFreeString(parms1[1].szName);
    SysFreeString(parms3[0].szName);
    SysFreeString(methdata[0].szName);
    SysFreeString(methdata[1].szName);
    SysFreeString(methdata[2].szName);
    SysFreeString(methdata[3].szName);
}