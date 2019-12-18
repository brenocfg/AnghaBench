#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sab ;
typedef  size_t VARTYPE ;
typedef  size_t UINT ;
struct TYPE_17__ {int fFeatures; } ;
struct TYPE_16__ {int cElements; scalar_t__ lLbound; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  TYPE_2__ SAFEARRAY ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DISP_E_ARRAYISLOCKED ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int FADF_HAVEIID ; 
 int FADF_HAVEVARTYPE ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int SAFEARRAY_GetVTSize (size_t) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* SafeArrayCreate (size_t,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  SafeArrayDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  SafeArrayDestroyData (TYPE_2__*) ; 
 int /*<<< orphan*/  SafeArrayDestroyDescriptor (TYPE_2__*) ; 
 size_t SafeArrayGetDim (TYPE_2__*) ; 
 int SafeArrayGetElemsize (TYPE_2__*) ; 
 int /*<<< orphan*/  SafeArrayLock (TYPE_2__*) ; 
 int /*<<< orphan*/  SafeArraySetIID (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArrayUnlock (TYPE_2__*) ; 
 size_t VT_CLSID ; 
 size_t VT_DISPATCH ; 
 size_t VT_EMPTY ; 
 size_t VT_R8 ; 
 size_t VT_RECORD ; 
 size_t VT_UI1 ; 
 size_t VT_UNKNOWN ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSafeArrayGetVartype (TYPE_2__*,size_t*) ; 

__attribute__((used)) static void test_SafeArrayCreateLockDestroy(void)
{
  SAFEARRAYBOUND sab[4];
  SAFEARRAY *sa;
  HRESULT hres;
  VARTYPE vt;
  UINT dimension;

  for (dimension = 0; dimension < ARRAY_SIZE(sab); dimension++)
  {
    sab[dimension].lLbound = 0;
    sab[dimension].cElements = 8;
  }

  /* Failure cases */
/* This test crashes very early versions with no error checking...
  sa = SafeArrayCreate(VT_UI1, 1, NULL);
  ok(sa == NULL, "NULL bounds didn't fail\n");
*/
  sa = SafeArrayCreate(VT_UI1, 65536, sab);
  ok(!sa, "Max bounds didn't fail\n");

  memset(sab, 0, sizeof(sab));

  /* Don't test 0 sized dimensions, as Windows has a bug which allows this */

  for (dimension = 0; dimension < ARRAY_SIZE(sab); dimension++)
    sab[dimension].cElements = 8;

  /* Test all VARTYPES in 1-4 dimensions */
  for (dimension = 1; dimension < 4; dimension++)
  {
    for (vt = VT_EMPTY; vt < VT_CLSID; vt++)
    {
      DWORD dwLen = SAFEARRAY_GetVTSize(vt);

      sa = SafeArrayCreate(vt, dimension, sab);

      if (dwLen)
        ok(sa != NULL, "VARTYPE %d (@%d dimensions) failed\n", vt, dimension);
      else
        ok(sa == NULL || vt == VT_R8,
           "VARTYPE %d (@%d dimensions) succeeded!\n", vt, dimension);

      if (sa)
      {
        ok(SafeArrayGetDim(sa) == dimension,
           "VARTYPE %d (@%d dimensions) cDims is %d, expected %d\n",
           vt, dimension, SafeArrayGetDim(sa), dimension);
        ok(SafeArrayGetElemsize(sa) == dwLen || vt == VT_R8,
           "VARTYPE %d (@%d dimensions) cbElements is %d, expected %d\n",
           vt, dimension, SafeArrayGetElemsize(sa), dwLen);

        if (vt != VT_UNKNOWN && vt != VT_DISPATCH)
        {
          ok((sa->fFeatures & FADF_HAVEIID) == 0,
             "Non interface type should not have FADF_HAVEIID\n");
          hres = SafeArraySetIID(sa, &IID_IUnknown);
          ok(hres == E_INVALIDARG, "Unexpected ret value %#x.\n", hres);
          if (vt != VT_RECORD)
          {
            VARTYPE aVt;

            ok(sa->fFeatures & FADF_HAVEVARTYPE,
               "Non interface type should have FADF_HAVEVARTYPE\n");
            if (pSafeArrayGetVartype)
            {
              hres = pSafeArrayGetVartype(sa, &aVt);
              ok(hres == S_OK && aVt == vt,
                 "Non interface type %d: bad type %d, hres %x\n", vt, aVt, hres);
            }
          }
        }
        else
        {
          ok(sa->fFeatures & FADF_HAVEIID, "Interface type should have FADF_HAVEIID\n");
          hres = SafeArraySetIID(sa, &IID_IUnknown);
          ok(hres == S_OK, "Failed to set array IID, hres %#x.\n", hres);
          ok((sa->fFeatures & FADF_HAVEVARTYPE) == 0,
             "Interface type %d should not have FADF_HAVEVARTYPE\n", vt);
        }

        hres = SafeArrayLock(sa);
        ok(hres == S_OK, "Lock VARTYPE %d (@%d dimensions) failed; hres 0x%x\n",
           vt, dimension, hres);

        if (hres == S_OK)
        {
          hres = SafeArrayDestroy(sa);
          ok(hres == DISP_E_ARRAYISLOCKED,"Destroy() got hres %x\n", hres);

          hres = SafeArrayDestroyData(sa);
          ok(hres == DISP_E_ARRAYISLOCKED,"DestroyData() got hres %x\n", hres);

          hres = SafeArrayDestroyDescriptor(sa);
          ok(hres == DISP_E_ARRAYISLOCKED,"DestroyDescriptor() got hres %x\n", hres);

          hres = SafeArrayUnlock(sa);
          ok(hres == S_OK, "Unlock VARTYPE %d (@%d dims) hres 0x%x\n",
             vt, dimension, hres);

          hres = SafeArrayDestroy(sa);
          ok(hres == S_OK, "destroy VARTYPE %d (@%d dims) hres 0x%x\n",
             vt, dimension, hres);
        }
      }
    }
  }
}