#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_6__ {int cElems; int /*<<< orphan*/  pElems; } ;
struct TYPE_7__ {TYPE_1__ caub; } ;
struct TYPE_8__ {int vt; TYPE_2__ u; } ;
typedef  TYPE_3__ PROPVARIANT ;
typedef  int LONG ;
typedef  int HRESULT ;

/* Variables and functions */
 int InitPropVariantFromBuffer (char const*,int,TYPE_3__*) ; 
 int InitVariantFromBuffer (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_3__*) ; 
 int S_OK ; 
 int SafeArrayAccessData (int /*<<< orphan*/ ,void**) ; 
 int SafeArrayGetDim (int /*<<< orphan*/ ) ; 
 int SafeArrayGetLBound (int /*<<< orphan*/ ,int,int*) ; 
 int SafeArrayGetUBound (int /*<<< orphan*/ ,int,int*) ; 
 int SafeArrayUnaccessData (int /*<<< orphan*/ ) ; 
 int VT_ARRAY ; 
 int VT_UI1 ; 
 int VT_VECTOR ; 
 int /*<<< orphan*/  V_ARRAY (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char const*,void*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_InitPropVariantFromBuffer(void)
{
    static const char data_in[] = "test";
    PROPVARIANT propvar;
    VARIANT var;
    HRESULT hres;
    void *data_out;
    LONG size;

    hres = InitPropVariantFromBuffer(NULL, 0, &propvar);
    ok(hres == S_OK, "InitPropVariantFromBuffer returned %x\n", hres);
    ok(propvar.vt == (VT_VECTOR|VT_UI1), "propvar.vt = %d\n", propvar.vt);
    ok(propvar.u.caub.cElems == 0, "cElems = %d\n", propvar.u.caub.cElems == 0);
    PropVariantClear(&propvar);

    hres = InitPropVariantFromBuffer(data_in, 4, &propvar);
    ok(hres == S_OK, "InitPropVariantFromBuffer returned %x\n", hres);
    ok(propvar.vt == (VT_VECTOR|VT_UI1), "propvar.vt = %d\n", propvar.vt);
    ok(propvar.u.caub.cElems == 4, "cElems = %d\n", propvar.u.caub.cElems == 0);
    ok(!memcmp(propvar.u.caub.pElems, data_in, 4), "Data inside array is incorrect\n");
    PropVariantClear(&propvar);

    hres = InitVariantFromBuffer(NULL, 0, &var);
    ok(hres == S_OK, "InitVariantFromBuffer returned %x\n", hres);
    ok(V_VT(&var) == (VT_ARRAY|VT_UI1), "V_VT(&var) = %d\n", V_VT(&var));
    size = SafeArrayGetDim(V_ARRAY(&var));
    ok(size == 1, "SafeArrayGetDim returned %d\n", size);
    hres = SafeArrayGetLBound(V_ARRAY(&var), 1, &size);
    ok(hres == S_OK, "SafeArrayGetLBound returned %x\n", hres);
    ok(size == 0, "LBound = %d\n", size);
    hres = SafeArrayGetUBound(V_ARRAY(&var), 1, &size);
    ok(hres == S_OK, "SafeArrayGetUBound returned %x\n", hres);
    ok(size == -1, "UBound = %d\n", size);
    VariantClear(&var);

    hres = InitVariantFromBuffer(data_in, 4, &var);
    ok(hres == S_OK, "InitVariantFromBuffer returned %x\n", hres);
    ok(V_VT(&var) == (VT_ARRAY|VT_UI1), "V_VT(&var) = %d\n", V_VT(&var));
    size = SafeArrayGetDim(V_ARRAY(&var));
    ok(size == 1, "SafeArrayGetDim returned %d\n", size);
    hres = SafeArrayGetLBound(V_ARRAY(&var), 1, &size);
    ok(hres == S_OK, "SafeArrayGetLBound returned %x\n", hres);
    ok(size == 0, "LBound = %d\n", size);
    hres = SafeArrayGetUBound(V_ARRAY(&var), 1, &size);
    ok(hres == S_OK, "SafeArrayGetUBound returned %x\n", hres);
    ok(size == 3, "UBound = %d\n", size);
    hres = SafeArrayAccessData(V_ARRAY(&var), &data_out);
    ok(hres == S_OK, "SafeArrayAccessData failed %x\n", hres);
    ok(!memcmp(data_in, data_out, 4), "Data inside safe array is incorrect\n");
    hres = SafeArrayUnaccessData(V_ARRAY(&var));
    ok(hres == S_OK, "SafeArrayUnaccessData failed %x\n", hres);
    VariantClear(&var);
}