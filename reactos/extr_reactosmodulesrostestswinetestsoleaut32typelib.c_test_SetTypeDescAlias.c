#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t ULONG ;
struct TYPE_7__ {scalar_t__ vt; } ;
struct TYPE_6__ {size_t cbSizeInstance; int cbAlignment; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  int SYSKIND ;
typedef  char OLECHAR ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  ICreateTypeLib2 ;
typedef  int /*<<< orphan*/  ICreateTypeInfo ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CreateTypeLib2 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeInfo_AddRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ICreateTypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeLib2_CreateTypeInfo (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ICreateTypeLib2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ ICreateTypeLib2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateTypeLib2_SaveAllChanges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ITypeInfo ; 
 int /*<<< orphan*/  IID_ITypeLib ; 
 scalar_t__ ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ITypeLib_GetTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ITypeLib_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadTypeLibEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  REGKIND_NONE ; 
#define  SYS_WIN32 129 
#define  SYS_WIN64 128 
 scalar_t__ S_OK ; 
 TYPE_2__* TDATests ; 
 int /*<<< orphan*/  TKIND_INTERFACE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  testTDA (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SetTypeDescAlias(SYSKIND kind)
{
    CHAR filenameA[MAX_PATH];
    WCHAR filenameW[MAX_PATH];
    ITypeLib *tl;
    ICreateTypeLib2 *ctl;
    ITypeInfo *ti;
    ICreateTypeInfo *cti;
    HREFTYPE hreftype;
    TYPEATTR *typeattr;
    ULONG href_cbSizeInstance, i;
    WORD href_cbAlignment, ptr_size;
    HRESULT hr;

    static OLECHAR interfaceW[] = {'i','n','t','e','r','f','a','c','e',0};

    switch(kind){
    case SYS_WIN32:
        trace("testing SYS_WIN32\n");
        ptr_size = 4;
        break;
    case SYS_WIN64:
        trace("testing SYS_WIN64\n");
        ptr_size = 8;
        break;
    default:
        return;
    }

    GetTempFileNameA(".", "tlb", 0, filenameA);
    MultiByteToWideChar(CP_ACP, 0, filenameA, -1, filenameW, MAX_PATH);

    hr = CreateTypeLib2(kind, filenameW, &ctl);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeLib2_CreateTypeInfo(ctl, interfaceW, TKIND_INTERFACE, &cti);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_QueryInterface(cti, &IID_ITypeInfo, (void**)&ti);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ICreateTypeInfo_AddRefTypeInfo(cti, ti, &hreftype);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(ti, &typeattr);
    ok(hr == S_OK, "got %08x\n", hr);

    href_cbSizeInstance = typeattr->cbSizeInstance;
    href_cbAlignment = typeattr->cbAlignment;

    ITypeInfo_ReleaseTypeAttr(ti, typeattr);

    ITypeInfo_Release(ti);
    ICreateTypeInfo_Release(cti);

    hr = ICreateTypeLib2_QueryInterface(ctl, &IID_ITypeLib, (void**)&tl);
    ok(hr == S_OK, "got %08x\n", hr);

    for(i = 0; TDATests[i].vt; ++i)
        testTDA(tl, &TDATests[i], ptr_size, hreftype, href_cbSizeInstance, href_cbAlignment, TRUE);

    hr = ICreateTypeLib2_SaveAllChanges(ctl);
    ok(hr == S_OK, "got %08x\n", hr);

    ITypeLib_Release(tl);
    ok(0 == ICreateTypeLib2_Release(ctl), "typelib should have been released\n");

    trace("after save...\n");

    hr = LoadTypeLibEx(filenameW, REGKIND_NONE, &tl);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ITypeLib_GetTypeInfo(tl, 0, &ti);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(ti, &typeattr);
    ok(hr == S_OK, "got %08x\n", hr);

    href_cbSizeInstance = typeattr->cbSizeInstance;
    href_cbAlignment = typeattr->cbAlignment;

    ITypeInfo_ReleaseTypeAttr(ti, typeattr);
    ITypeInfo_Release(ti);

    for(i = 0; TDATests[i].vt; ++i)
        testTDA(tl, &TDATests[i], ptr_size, hreftype, href_cbSizeInstance, href_cbAlignment, FALSE);

    ok(0 == ITypeLib_Release(tl), "typelib should have been released\n");

    DeleteFileA(filenameA);
}