#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_16__ {int ref; int sizeCalled; int clearCalled; int recordcopy; int /*<<< orphan*/  IRecordInfo_iface; } ;
struct TYPE_15__ {int cbElements; } ;
struct TYPE_14__ {int cElements; scalar_t__ lLbound; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  TYPE_2__ SAFEARRAY ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_3__ IRecordInfoImpl ;
typedef  int /*<<< orphan*/  IRecordInfo ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_ITypeInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 TYPE_3__* IRecordInfoImpl_Construct () ; 
 int /*<<< orphan*/  IRecordInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RECORD_SIZE ; 
 int RECORD_SIZE_FAIL ; 
 int START_REF_COUNT ; 
 int S_OK ; 
 int SafeArrayCopyData (TYPE_2__*,TYPE_2__*) ; 
 int SafeArrayDestroy (TYPE_2__*) ; 
 int SafeArrayGetIID (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int SafeArraySetIID (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VT_DISPATCH ; 
 int /*<<< orphan*/  VT_RECORD ; 
 int /*<<< orphan*/  VT_UI1 ; 
 int /*<<< orphan*/  VT_UNKNOWN ; 
 int /*<<< orphan*/  fail_GetSize ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_2__* pSafeArrayCreateEx (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pSafeArrayGetRecordInfo (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SafeArrayCreateEx(void)
{
  IRecordInfoImpl* iRec;
  SAFEARRAYBOUND sab[4];
  SAFEARRAY *sa;
  HRESULT hres;
  UINT dimension;

  if (!pSafeArrayCreateEx)
  {
    win_skip("SafeArrayCreateEx not supported\n");
    return;
  }

  for (dimension = 0; dimension < ARRAY_SIZE(sab); dimension++)
  {
    sab[dimension].lLbound = 0;
    sab[dimension].cElements = 8;
  }

  /* Failure cases */
  sa = pSafeArrayCreateEx(VT_UI1, 1, NULL, NULL);
  ok(sa == NULL, "CreateEx NULL bounds didn't fail\n");

  /* test IID storage & defaulting */
  sa = pSafeArrayCreateEx(VT_DISPATCH, 1, sab, (PVOID)&IID_ITypeInfo);
  ok(sa != NULL, "CreateEx (ITypeInfo) failed\n");

  if (sa)
  {
    GUID guid;

    hres = SafeArrayGetIID(sa, &guid);
    ok(hres == S_OK, "Failed to get array IID, hres %#x.\n", hres);
    ok(IsEqualGUID(&guid, &IID_ITypeInfo), "CreateEx (ITypeInfo) bad IID\n");
    hres = SafeArraySetIID(sa, &IID_IUnknown);
    ok(hres == S_OK, "Failed to set IID, hres = %8x\n", hres);
    hres = SafeArrayGetIID(sa, &guid);
    ok(hres == S_OK && IsEqualGUID(&guid, &IID_IUnknown), "Set bad IID\n");
    hres = SafeArrayDestroy(sa);
    ok(hres == S_OK, "got 0x%08x\n", hres);
  }

  sa = pSafeArrayCreateEx(VT_DISPATCH, 1, sab, NULL);
  ok(sa != NULL, "CreateEx (NULL) failed\n");

  if (sa)
  {
    GUID guid;

    hres = SafeArrayGetIID(sa, &guid);
    ok(hres == S_OK, "Failed to get array IID, hres %#x.\n", hres);
    ok(IsEqualGUID(&guid, &IID_IDispatch), "CreateEx (NULL) bad IID\n");
    hres = SafeArrayDestroy(sa);
    ok(hres == S_OK, "got 0x%08x\n", hres);
  }

  sa = pSafeArrayCreateEx(VT_UNKNOWN, 1, sab, NULL);
  ok(sa != NULL, "CreateEx (NULL-Unk) failed\n");

  if (sa)
  {
    GUID guid;

    hres = SafeArrayGetIID(sa, &guid);
    ok(hres == S_OK, "Failed to get array IID, hres %#x.\n", hres);
    ok(IsEqualGUID(&guid, &IID_IUnknown), "CreateEx (NULL-Unk) bad IID\n");
    hres = SafeArrayDestroy(sa);
    ok(hres == S_OK, "got 0x%08x\n", hres);
  }

  /* VT_RECORD failure case */
  sa = pSafeArrayCreateEx(VT_RECORD, 1, sab, NULL);
  ok(sa == NULL, "CreateEx (NULL-Rec) succeeded\n");

  iRec = IRecordInfoImpl_Construct();

  /* Win32 doesn't care if GetSize fails */
  fail_GetSize = TRUE;
  sa = pSafeArrayCreateEx(VT_RECORD, 1, sab, &iRec->IRecordInfo_iface);
  ok(sa != NULL, "CreateEx (Fail Size) failed\n");
  ok(iRec->ref == START_REF_COUNT + 1, "Wrong iRec refcount %d\n", iRec->ref);
  ok(iRec->sizeCalled == 1, "GetSize called %d times\n", iRec->sizeCalled);
  ok(iRec->clearCalled == 0, "Clear called %d times\n", iRec->clearCalled);
  if (sa)
  {
    ok(sa->cbElements == RECORD_SIZE_FAIL, "Altered size to %d\n", sa->cbElements);
    hres = SafeArrayDestroy(sa);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iRec->clearCalled == sab[0].cElements, "Destroy->Clear called %d times\n", iRec->clearCalled);
    ok(iRec->ref == START_REF_COUNT, "got %d, expected %d\n", iRec->ref, START_REF_COUNT);
  }

  /* Test VT_RECORD array */
  fail_GetSize = FALSE;
  iRec->ref = START_REF_COUNT;
  iRec->sizeCalled = 0;
  iRec->clearCalled = 0;
  sa = pSafeArrayCreateEx(VT_RECORD, 1, sab, &iRec->IRecordInfo_iface);
  ok(sa != NULL, "CreateEx (Rec) failed\n");
  ok(iRec->ref == START_REF_COUNT + 1, "Wrong iRec refcount %d\n", iRec->ref);
  ok(iRec->sizeCalled == 1, "GetSize called %d times\n", iRec->sizeCalled);
  ok(iRec->clearCalled == 0, "Clear called %d times\n", iRec->clearCalled);
  if (sa && pSafeArrayGetRecordInfo)
  {
    IRecordInfo* saRec = NULL;
    SAFEARRAY *sacopy;

    hres = pSafeArrayGetRecordInfo(sa, &saRec);
    ok(hres == S_OK,"GRI failed\n");
    ok(saRec == &iRec->IRecordInfo_iface, "Different saRec\n");
    ok(iRec->ref == START_REF_COUNT + 2, "Didn't AddRef %d\n", iRec->ref);
    IRecordInfo_Release(saRec);

    ok(sa->cbElements == RECORD_SIZE,"Elemsize is %d\n", sa->cbElements);

    /* try to copy record based arrays */
    sacopy = pSafeArrayCreateEx(VT_RECORD, 1, sab, &iRec->IRecordInfo_iface);
    iRec->recordcopy = 0;
    iRec->clearCalled = 0;
    /* array copy code doesn't explicitly clear a record */
    hres = SafeArrayCopyData(sa, sacopy);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iRec->recordcopy == sab[0].cElements, "got %d\n", iRec->recordcopy);
    ok(iRec->clearCalled == 0, "got %d\n", iRec->clearCalled);

    hres = SafeArrayDestroy(sacopy);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    iRec->clearCalled = 0;
    iRec->sizeCalled = 0;
    hres = SafeArrayDestroy(sa);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iRec->sizeCalled == 0, "Destroy->GetSize called %d times\n", iRec->sizeCalled);
    ok(iRec->clearCalled == sab[0].cElements, "Destroy->Clear called %d times\n", iRec->clearCalled);
    ok(iRec->ref == START_REF_COUNT, "Wrong iRec refcount %d\n", iRec->ref);
  }
  else
  {
    hres = SafeArrayDestroy(sa);
    ok(hres == S_OK, "got 0x%08x\n", hres);
  }

  IRecordInfo_Release(&iRec->IRecordInfo_iface);
}