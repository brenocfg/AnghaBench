#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_11__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_2__ GUID ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 TYPE_2__ CLSID_FileProtocol ; 
 TYPE_2__ CLSID_NULL ; 
 scalar_t__ CoCreateInstance (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int /*<<< orphan*/  IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ REGDB_E_WRITEREGDB ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCoGetTreatAsClass (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ pCoTreatAsClass (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  win_skip (char*,...) ; 

__attribute__((used)) static void test_TreatAsClass(void)
{
    HRESULT hr;
    CLSID out;
    static GUID deadbeef = {0xdeadbeef,0xdead,0xbeef,{0xde,0xad,0xbe,0xef,0xde,0xad,0xbe,0xef}};
    static const char deadbeefA[] = "{DEADBEEF-DEAD-BEEF-DEAD-BEEFDEADBEEF}";
    IInternetProtocol *pIP = NULL;
    HKEY clsidkey, deadbeefkey;
    LONG lr;

    if (!pCoGetTreatAsClass)
    {
        win_skip("CoGetTreatAsClass not present\n");
        return;
    }

    hr = pCoGetTreatAsClass(&deadbeef,&out);
    ok (hr == S_FALSE, "expected S_FALSE got %x\n",hr);
    ok (IsEqualGUID(&out,&deadbeef), "expected to get same clsid back\n");

    hr = pCoGetTreatAsClass(NULL, &out);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr);
    ok(IsEqualGUID(&out, &deadbeef), "expected no change to the clsid\n");

    hr = pCoGetTreatAsClass(&deadbeef, NULL);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr);

    lr = RegOpenKeyExA(HKEY_CLASSES_ROOT, "CLSID", 0, KEY_READ, &clsidkey);
    ok(!lr, "Couldn't open CLSID key, error %d\n", lr);

    lr = RegCreateKeyExA(clsidkey, deadbeefA, 0, NULL, 0, KEY_WRITE, NULL, &deadbeefkey, NULL);
    if (lr) {
        win_skip("CoGetTreatAsClass() tests will be skipped (failed to create a test key, error %d)\n", lr);
        RegCloseKey(clsidkey);
        return;
    }

    hr = pCoTreatAsClass(&deadbeef, &deadbeef);
    ok(hr == REGDB_E_WRITEREGDB, "CoTreatAsClass gave wrong error: %08x\n", hr);

    hr = pCoTreatAsClass(&deadbeef, &CLSID_FileProtocol);
    if(hr == REGDB_E_WRITEREGDB){
        win_skip("Insufficient privileges to use CoTreatAsClass\n");
        goto exit;
    }
    ok(hr == S_OK, "CoTreatAsClass failed: %08x\n", hr);

    hr = pCoGetTreatAsClass(&deadbeef, &out);
    ok(hr == S_OK, "CoGetTreatAsClass failed: %08x\n",hr);
    ok(IsEqualGUID(&out, &CLSID_FileProtocol), "expected to get substituted clsid\n");

    OleInitialize(NULL);

    hr = CoCreateInstance(&deadbeef, NULL, CLSCTX_INPROC_SERVER, &IID_IInternetProtocol, (void **)&pIP);
    if(hr == REGDB_E_CLASSNOTREG)
    {
        win_skip("IE not installed so can't test CoCreateInstance\n");
        goto exit;
    }

    ok(hr == S_OK, "CoCreateInstance failed: %08x\n", hr);
    if(pIP){
        IInternetProtocol_Release(pIP);
        pIP = NULL;
    }

    hr = pCoTreatAsClass(&deadbeef, &CLSID_NULL);
    ok(hr == S_OK, "CoTreatAsClass failed: %08x\n", hr);

    hr = pCoGetTreatAsClass(&deadbeef, &out);
    ok(hr == S_FALSE, "expected S_FALSE got %08x\n", hr);
    ok(IsEqualGUID(&out, &deadbeef), "expected to get same clsid back\n");

    /* bizarrely, native's CoTreatAsClass takes some time to take effect in CoCreateInstance */
    Sleep(200);

    hr = CoCreateInstance(&deadbeef, NULL, CLSCTX_INPROC_SERVER, &IID_IInternetProtocol, (void **)&pIP);
    ok(hr == REGDB_E_CLASSNOTREG, "CoCreateInstance gave wrong error: %08x\n", hr);

    if(pIP)
        IInternetProtocol_Release(pIP);

exit:
    OleUninitialize();
    RegCloseKey(deadbeefkey);
    RegDeleteKeyA(clsidkey, deadbeefA);
    RegCloseKey(clsidkey);
}