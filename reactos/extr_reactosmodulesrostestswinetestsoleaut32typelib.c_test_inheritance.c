#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_16__ {int Data1; } ;
struct TYPE_15__ {int vt; } ;
struct TYPE_14__ {int hreftype; } ;
struct TYPE_13__ {int memid; int oVft; int cParams; TYPE_1__* lprgelemdescParam; } ;
struct TYPE_12__ {int typekind; int cbSizeVft; int wTypeFlags; int cFuncs; int cImplTypes; TYPE_6__ guid; } ;
struct TYPE_11__ {TYPE_5__ tdesc; } ;
typedef  TYPE_2__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int HRESULT ;
typedef  int HREFTYPE ;
typedef  TYPE_3__ FUNCDESC ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DIID_ItestIF10 ; 
 int /*<<< orphan*/  DIID_ItestIF11 ; 
 int /*<<< orphan*/  DIID_ItestIF3 ; 
 int /*<<< orphan*/  DIID_ItestIF4 ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_ItestIF2 ; 
 int /*<<< orphan*/  IID_ItestIF5 ; 
 int /*<<< orphan*/  IID_ItestIF7 ; 
 int ITypeInfo_GetFuncDesc (int /*<<< orphan*/ *,int,TYPE_3__**) ; 
 int ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int,int*) ; 
 int ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseFuncDesc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int LoadTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int TKIND_DISPATCH ; 
 int TKIND_INTERFACE ; 
 int TYPEFLAG_FDISPATCHABLE ; 
 int TYPEFLAG_FDUAL ; 
 int TYPE_E_ELEMENTNOTFOUND ; 
 TYPE_4__ U (TYPE_5__) ; 
 int VT_USERDEFINED ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_inheritance(void)
{
    HRESULT hr;
    ITypeLib *pTL;
    ITypeInfo *pTI, *pTI_p;
    TYPEATTR *pTA;
    HREFTYPE href;
    FUNCDESC *pFD;
    WCHAR path[MAX_PATH];
    CHAR pathA[MAX_PATH];

    GetModuleFileNameA(NULL, pathA, MAX_PATH);
    MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);

    hr = LoadTypeLib(path, &pTL);
    if(FAILED(hr)) return;


    /* ItestIF3 is a syntax 2 dispinterface */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &DIID_ItestIF3, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_DISPATCH, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 7 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == TYPEFLAG_FDISPATCHABLE, "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 6, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    hr = ITypeInfo_GetRefTypeOfImplType(pTI, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI_p, &pTA);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(IsEqualGUID(&pTA->guid, &IID_IDispatch), "guid {%08x-....\n", pTA->guid.Data1);
    ITypeInfo_ReleaseTypeAttr(pTI_p, pTA);
    ITypeInfo_Release(pTI_p);

    /* Should have six methods */
    hr = ITypeInfo_GetFuncDesc(pTI, 6, &pFD);
    ok(hr == TYPE_E_ELEMENTNOTFOUND, "hr %08x\n", hr);
    hr = ITypeInfo_GetFuncDesc(pTI, 5, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x60020000, "memid %08x\n", pFD->memid);
    ok(pFD->oVft == 5 * sizeof(void *), "oVft %d\n", pFD->oVft);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);


    /* ItestIF4 is a syntax 1 dispinterface */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &DIID_ItestIF4, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_DISPATCH, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 7 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == TYPEFLAG_FDISPATCHABLE, "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 1, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    hr = ITypeInfo_GetRefTypeOfImplType(pTI, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI_p, &pTA);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(IsEqualGUID(&pTA->guid, &IID_IDispatch), "guid {%08x-....\n", pTA->guid.Data1);
    ITypeInfo_ReleaseTypeAttr(pTI_p, pTA);
    ITypeInfo_Release(pTI_p);
    hr = ITypeInfo_GetFuncDesc(pTI, 1, &pFD);
    ok(hr == TYPE_E_ELEMENTNOTFOUND, "hr %08x\n", hr);
    hr = ITypeInfo_GetFuncDesc(pTI, 0, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x1c, "memid %08x\n", pFD->memid);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);


    /* ItestIF5 is dual with inherited ifaces which derive from IUnknown but not IDispatch */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &IID_ItestIF5, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_DISPATCH, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 7 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == TYPEFLAG_FDUAL, "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 8, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    hr = ITypeInfo_GetRefTypeOfImplType(pTI, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI_p, &pTA);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(IsEqualGUID(&pTA->guid, &IID_IDispatch), "guid {%08x-....\n", pTA->guid.Data1);
    ITypeInfo_ReleaseTypeAttr(pTI_p, pTA);
    ITypeInfo_Release(pTI_p);
    hr = ITypeInfo_GetFuncDesc(pTI, 6, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x1234, "memid %08x\n", pFD->memid);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);

    /* ItestIF7 is dual with inherited ifaces which derive from Dispatch */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &IID_ItestIF7, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_DISPATCH, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 7 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == (TYPEFLAG_FDISPATCHABLE|TYPEFLAG_FDUAL), "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 10, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    hr = ITypeInfo_GetRefTypeOfImplType(pTI, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI_p, &pTA);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(IsEqualGUID(&pTA->guid, &IID_IDispatch), "guid {%08x-....\n", pTA->guid.Data1);
    ITypeInfo_ReleaseTypeAttr(pTI_p, pTA);
    ITypeInfo_Release(pTI_p);

    hr = ITypeInfo_GetFuncDesc(pTI, 9, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x1236, "memid %08x\n", pFD->memid);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);

    /* ItestIF10 is a syntax 2 dispinterface which doesn't derive from IUnknown */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &DIID_ItestIF10, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_DISPATCH, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 7 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == TYPEFLAG_FDISPATCHABLE, "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 3, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    hr = ITypeInfo_GetRefTypeOfImplType(pTI, -1, &href);
    ok(hr == TYPE_E_ELEMENTNOTFOUND, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeOfImplType(pTI, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI_p, &pTA);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(IsEqualGUID(&pTA->guid, &IID_IDispatch), "guid {%08x-....\n", pTA->guid.Data1);
    ITypeInfo_ReleaseTypeAttr(pTI_p, pTA);
    ITypeInfo_Release(pTI_p);

    /* Should have three methods */
    hr = ITypeInfo_GetFuncDesc(pTI, 3, &pFD);
    ok(hr == TYPE_E_ELEMENTNOTFOUND, "hr %08x\n", hr);
    hr = ITypeInfo_GetFuncDesc(pTI, 2, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x60010000, "memid %08x\n", pFD->memid);
    ok(pFD->oVft == 2 * sizeof(void *), "oVft %d\n", pFD->oVft);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);

    /* ItestIF11 is a syntax 2 dispinterface which derives from IDispatch */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &DIID_ItestIF11, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_DISPATCH, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 7 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == TYPEFLAG_FDISPATCHABLE, "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 10, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    hr = ITypeInfo_GetRefTypeOfImplType(pTI, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI_p, &pTA);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(IsEqualGUID(&pTA->guid, &IID_IDispatch), "guid {%08x-....\n", pTA->guid.Data1);
    ITypeInfo_ReleaseTypeAttr(pTI_p, pTA);
    ITypeInfo_Release(pTI_p);

    /* Should have ten methods */
    hr = ITypeInfo_GetFuncDesc(pTI, 10, &pFD);
    ok(hr == TYPE_E_ELEMENTNOTFOUND, "hr %08x\n", hr);
    hr = ITypeInfo_GetFuncDesc(pTI, 9, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x1236, "memid %08x\n", pFD->memid);
    ok(pFD->oVft == 9 * sizeof(void *), "oVft %d\n", pFD->oVft);

    /* first argument to 10th function is an HREFTYPE from the impl type */
    ok(pFD->cParams == 1, "cParams %i\n", pFD->cParams);
    ok(pFD->lprgelemdescParam[0].tdesc.vt == VT_USERDEFINED,
        "vt 0x%x\n", pFD->lprgelemdescParam[0].tdesc.vt);
    href = U(pFD->lprgelemdescParam[0].tdesc).hreftype;
    ok((href & 0xff000000) == 0x04000000, "href 0x%08x\n", href);
    hr = ITypeInfo_GetRefTypeInfo(pTI, href, &pTI_p);
    ok(hr == S_OK, "hr %08x\n", hr);
    if (SUCCEEDED(hr)) ITypeInfo_Release(pTI_p);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);


    /* ItestIF2 is an interface which derives from IUnknown */
    hr = ITypeLib_GetTypeInfoOfGuid(pTL, &IID_ItestIF2, &pTI);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTI, &pTA);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTA->typekind == TKIND_INTERFACE, "kind %04x\n", pTA->typekind);
    ok(pTA->cbSizeVft == 6 * sizeof(void *), "sizevft %d\n", pTA->cbSizeVft);
    ok(pTA->wTypeFlags == 0, "typeflags %x\n", pTA->wTypeFlags);
    ok(pTA->cFuncs == 1, "cfuncs %d\n", pTA->cFuncs);
    ok(pTA->cImplTypes == 1, "cimpltypes %d\n", pTA->cImplTypes);
    ITypeInfo_ReleaseTypeAttr(pTI, pTA);

    /* Should have one method */
    hr = ITypeInfo_GetFuncDesc(pTI, 1, &pFD);
    ok(hr == TYPE_E_ELEMENTNOTFOUND, "hr %08x\n", hr);
    hr = ITypeInfo_GetFuncDesc(pTI, 0, &pFD);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFD->memid == 0x60020000, "memid %08x\n", pFD->memid);
    ok(pFD->oVft == 5 * sizeof(void *), "oVft %d\n", pFD->oVft);
    ITypeInfo_ReleaseFuncDesc(pTI, pFD);
    ITypeInfo_Release(pTI);

    ITypeLib_Release(pTL);

    return;
}