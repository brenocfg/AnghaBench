#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ref; int /*<<< orphan*/  IUnknown_iface; } ;
struct TYPE_10__ {int cbElements; } ;
struct TYPE_9__ {int lLbound; int cElements; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  TYPE_2__ SAFEARRAY ;
typedef  int /*<<< orphan*/  LPUNKNOWN ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* SafeArrayCreate (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  SafeArrayDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  SafeArrayGetElement (TYPE_2__*,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SafeArrayPutElement (TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VT_UNKNOWN ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_3__ xtunk ; 

__attribute__((used)) static void test_SafeArrayGetPutElement_IUnknown(void)
{
  SAFEARRAYBOUND sab;
  LONG indices[1];
  SAFEARRAY *sa;
  HRESULT hres;
  IUnknown *gotvalue;

  sab.lLbound = 1;
  sab.cElements = 1;
  sa = SafeArrayCreate(VT_UNKNOWN, 1, &sab);
  ok(sa != NULL, "UNKNOWN test couldn't create array\n");
  if (!sa)
    return;

  ok(sa->cbElements == sizeof(LPUNKNOWN), "LPUNKNOWN size mismatch\n");

  indices[0] = sab.lLbound;
  xtunk.ref = 1;
  hres = SafeArrayPutElement(sa, indices, &xtunk.IUnknown_iface);
  ok(hres == S_OK, "Failed to put bstr element hres 0x%x\n", hres);
  ok(xtunk.ref == 2,"Failed to increment refcount of iface.\n");
  gotvalue = NULL;
  hres = SafeArrayGetElement(sa, indices, &gotvalue);
  ok(xtunk.ref == 3,"Failed to increment refcount of iface.\n");
  ok(hres == S_OK, "Failed to get bstr element at hres 0x%x\n", hres);
  if (hres == S_OK)
    ok(gotvalue == &xtunk.IUnknown_iface, "Got %p instead of %p\n", gotvalue, &xtunk.IUnknown_iface);
  hres = SafeArrayDestroy(sa);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(xtunk.ref == 2,"Failed to decrement refcount of iface.\n");
}