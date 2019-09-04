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
typedef  int /*<<< orphan*/  startup ;
struct TYPE_7__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_6__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int E_FAIL ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int LresultFromObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  Object ; 
 int ObjectFromLresult (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int Object_ref ; 
 int SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_LresultFromObject(const char *name)
{
    PROCESS_INFORMATION proc;
    STARTUPINFOA startup;
    char cmdline[MAX_PATH];
    IUnknown *unk;
    HRESULT hres;
    LRESULT lres;

    lres = LresultFromObject(NULL, 0, 0);
    ok(lres == E_INVALIDARG, "got %lx\n", lres);

    hres = ObjectFromLresult(0, &IID_IUnknown, 0, (void**)&unk);
    ok(hres == E_FAIL, "got %x\n", hres);
    hres = ObjectFromLresult(0x10000, &IID_IUnknown, 0, (void**)&unk);
    ok(hres == E_FAIL, "got %x\n", hres);

    ok(Object_ref == 1, "Object_ref = %d\n", Object_ref);
    lres = LresultFromObject(&IID_IUnknown, 0, &Object);
    ok(SUCCEEDED(lres), "got %lx\n", lres);
    ok(Object_ref > 1, "Object_ref = %d\n", Object_ref);

    hres = ObjectFromLresult(lres, &IID_IUnknown, 0, (void**)&unk);
    ok(hres == S_OK, "hres = %x\n", hres);
    ok(unk == &Object, "unk != &Object\n");
    IUnknown_Release(unk);
    ok(Object_ref == 1, "Object_ref = %d\n", Object_ref);

    lres = LresultFromObject(&IID_IUnknown, 0, &Object);
    ok(SUCCEEDED(lres), "got %lx\n", lres);
    ok(Object_ref > 1, "Object_ref = %d\n", Object_ref);

    sprintf(cmdline, "\"%s\" main ObjectFromLresult %lx", name, lres);
    memset(&startup, 0, sizeof(startup));
    startup.cb = sizeof(startup);
    CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &startup, &proc);
    winetest_wait_child_process(proc.hProcess);
    ok(Object_ref == 1, "Object_ref = %d\n", Object_ref);
}