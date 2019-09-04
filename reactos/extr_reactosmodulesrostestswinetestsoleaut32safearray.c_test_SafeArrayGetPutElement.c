#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
struct TYPE_15__ {int ref; int recordcopy; int /*<<< orphan*/  IRecordInfo_iface; } ;
struct TYPE_14__ {int cbElements; } ;
struct TYPE_13__ {int lLbound; int cElements; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  TYPE_2__ SAFEARRAY ;
typedef  int LONG ;
typedef  TYPE_3__ IRecordInfoImpl ;
typedef  unsigned int HRESULT ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int DISP_E_BADINDEX ; 
 unsigned int E_INVALIDARG ; 
 TYPE_3__* IRecordInfoImpl_Construct () ; 
 int /*<<< orphan*/  IRecordInfo_Release (int /*<<< orphan*/ *) ; 
 unsigned int S_OK ; 
 TYPE_2__* SafeArrayCreate (int /*<<< orphan*/ ,unsigned int,TYPE_1__*) ; 
 unsigned int SafeArrayDestroy (TYPE_2__*) ; 
 unsigned int SafeArrayGetElement (TYPE_2__*,int*,void*) ; 
 unsigned int SafeArrayPutElement (TYPE_2__*,int*,void*) ; 
 int /*<<< orphan*/  VT_INT ; 
 int /*<<< orphan*/  VT_RECORD ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_2__* pSafeArrayCreateEx (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_SafeArrayGetPutElement(void)
{
  SAFEARRAYBOUND sab[4];
  LONG indices[ARRAY_SIZE(sab)], index;
  SAFEARRAY *sa;
  HRESULT hres;
  int value = 0, gotvalue, dimension;
  IRecordInfoImpl *irec;
  unsigned int x,y,z,a;

  for (dimension = 0; dimension < ARRAY_SIZE(sab); dimension++)
  {
    sab[dimension].lLbound = dimension * 2 + 1;
    sab[dimension].cElements = dimension * 3 + 1;
  }

  sa = SafeArrayCreate(VT_INT, ARRAY_SIZE(sab), sab);
  if (!sa)
    return; /* Some early versions can't handle > 3 dims */

  ok(sa->cbElements == sizeof(value), "int size mismatch\n");

  /* Failure cases */
  for (x = 0; x < ARRAY_SIZE(sab); x++)
  {
    indices[0] = sab[0].lLbound;
    indices[1] = sab[1].lLbound;
    indices[2] = sab[2].lLbound;
    indices[3] = sab[3].lLbound;

    indices[x] = indices[x] - 1;
    hres = SafeArrayPutElement(sa, indices, &value);
    ok(hres == DISP_E_BADINDEX, "Put allowed too small index in dimension %d\n", x);
    hres = SafeArrayGetElement(sa, indices, &value);
    ok(hres == DISP_E_BADINDEX, "Get allowed too small index in dimension %d\n", x);

    indices[x] = sab[x].lLbound + sab[x].cElements;
    hres = SafeArrayPutElement(sa, indices, &value);
    ok(hres == DISP_E_BADINDEX, "Put allowed too big index in dimension %d\n", x);
    hres = SafeArrayGetElement(sa, indices, &value);
    ok(hres == DISP_E_BADINDEX, "Get allowed too big index in dimension %d\n", x);
  }

  indices[0] = sab[0].lLbound;
  indices[1] = sab[1].lLbound;
  indices[2] = sab[2].lLbound;
  indices[3] = sab[3].lLbound;

  hres = SafeArrayPutElement(NULL, indices, &value);
  ok(hres == E_INVALIDARG, "Put NULL array hres 0x%x\n", hres);
  hres = SafeArrayGetElement(NULL, indices, &value);
  ok(hres == E_INVALIDARG, "Get NULL array hres 0x%x\n", hres);

  hres = SafeArrayPutElement(sa, NULL, &value);
  ok(hres == E_INVALIDARG, "Put NULL indices hres 0x%x\n", hres);
  hres = SafeArrayGetElement(sa, NULL, &value);
  ok(hres == E_INVALIDARG, "Get NULL indices hres 0x%x\n", hres);

  if (0)
  {
  /* This is retarded. Windows checks every case of invalid parameters
   * except the following, which crashes. We ERR this in Wine.
   */
  hres = SafeArrayPutElement(sa, indices, NULL);
  ok(hres == E_INVALIDARG, "Put NULL value hres 0x%x\n", hres);
  }

  hres = SafeArrayGetElement(sa, indices, NULL);
  ok(hres == E_INVALIDARG, "Get NULL value hres 0x%x\n", hres);

  value = 0;

  /* Make sure we can read and get back the correct values in 4 dimensions,
   * Each with a different size and lower bound.
   */
  for (x = 0; x < sab[0].cElements; x++)
  {
    indices[0] = sab[0].lLbound + x;
    for (y = 0; y < sab[1].cElements; y++)
    {
      indices[1] = sab[1].lLbound + y;
      for (z = 0; z < sab[2].cElements; z++)
      {
        indices[2] = sab[2].lLbound + z;
        for (a = 0; a < sab[3].cElements; a++)
        {
          indices[3] = sab[3].lLbound + a;
          hres = SafeArrayPutElement(sa, indices, &value);
          ok(hres == S_OK, "Failed to put element at (%d,%d,%d,%d) hres 0x%x\n",
             x, y, z, a, hres);
          value++;
        }
      }
    }
  }

  value = 0;

  for (x = 0; x < sab[0].cElements; x++)
  {
    indices[0] = sab[0].lLbound + x;
    for (y = 0; y < sab[1].cElements; y++)
    {
      indices[1] = sab[1].lLbound + y;
      for (z = 0; z < sab[2].cElements; z++)
      {
        indices[2] = sab[2].lLbound + z;
        for (a = 0; a < sab[3].cElements; a++)
        {
          indices[3] = sab[3].lLbound + a;
          gotvalue = value / 3;
          hres = SafeArrayGetElement(sa, indices, &gotvalue);
          ok(hres == S_OK, "Failed to get element at (%d,%d,%d,%d) hres 0x%x\n",
             x, y, z, a, hres);
          if (hres == S_OK)
            ok(value == gotvalue, "Got value %d instead of %d at (%d,%d,%d,%d)\n",
               gotvalue, value, x, y, z, a);
          value++;
        }
      }
    }
  }
  hres = SafeArrayDestroy(sa);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* VT_RECORD array */
  irec = IRecordInfoImpl_Construct();
  irec->ref = 1;

  sab[0].lLbound = 0;
  sab[0].cElements = 8;

  sa = pSafeArrayCreateEx(VT_RECORD, 1, sab, &irec->IRecordInfo_iface);
  ok(sa != NULL, "failed to create array\n");
  ok(irec->ref == 2, "got %d\n", irec->ref);

  index = 0;
  irec->recordcopy = 0;
  hres = SafeArrayPutElement(sa, &index, (void*)0xdeadbeef);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(irec->recordcopy == 1, "got %d\n", irec->recordcopy);

  index = 0;
  irec->recordcopy = 0;
  hres = SafeArrayGetElement(sa, &index, (void*)0xdeadbeef);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(irec->recordcopy == 1, "got %d\n", irec->recordcopy);

  hres = SafeArrayDestroy(sa);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(irec->ref == 1, "got %d\n", irec->ref);
  IRecordInfo_Release(&irec->IRecordInfo_iface);
}