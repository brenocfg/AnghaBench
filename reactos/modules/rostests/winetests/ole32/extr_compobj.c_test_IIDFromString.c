#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iid ;
typedef  char WCHAR ;
struct TYPE_6__ {int Data1; } ;
typedef  TYPE_1__ IID ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_NULL ; 
 int /*<<< orphan*/  CLSID_StdFont ; 
 int CO_E_IIDSTRING ; 
 int E_INVALIDARG ; 
 int IIDFromString (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int IsEqualIID (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 char const* cf_brokenW ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 char const* stdfont ; 
 int wine_dbgstr_guid (TYPE_1__*) ; 
 char const* wszCLSID_StdFont ; 
 char const* wszNonExistent ; 

__attribute__((used)) static void test_IIDFromString(void)
{
    static const WCHAR cfW[] = {'{','0','0','0','0','0','0','0','1','-','0','0','0','0','-','0','0','0','0','-',
                                    'c','0','0','0','-','0','0','0','0','0','0','0','0','0','0','4','6','}',0};
    static const WCHAR brokenW[] = {'{','0','0','0','0','0','0','0','1','-','0','0','0','0','-','0','0','0','0','-',
                                        'g','0','0','0','-','0','0','0','0','0','0','0','0','0','0','4','6','}',0};
    static const WCHAR broken2W[] = {'{','0','0','0','0','0','0','0','1','=','0','0','0','0','-','0','0','0','0','-',
                                        'g','0','0','0','-','0','0','0','0','0','0','0','0','0','0','4','6','}',0};
    static const WCHAR broken3W[] = {'b','r','o','k','e','n','0','0','1','=','0','0','0','0','-','0','0','0','0','-',
                                        'g','0','0','0','-','0','0','0','0','0','0','0','0','0','0','4','6','}',0};
    HRESULT hr;
    IID iid;

    hr = IIDFromString(wszCLSID_StdFont, &iid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualIID(&iid, &CLSID_StdFont), "got iid %s\n", wine_dbgstr_guid(&iid));

    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(NULL, &iid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualIID(&iid, &CLSID_NULL), "got iid %s\n", wine_dbgstr_guid(&iid));

    hr = IIDFromString(cfW, &iid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualIID(&iid, &IID_IClassFactory), "got iid %s\n", wine_dbgstr_guid(&iid));

    /* string starts with a valid IID but is longer */
    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(cf_brokenW, &iid);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(iid.Data1 == 0xabababab, "Got %08x\n", iid.Data1);

    /* invalid IID in a valid format */
    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(brokenW, &iid);
    ok(hr == CO_E_IIDSTRING, "got 0x%08x\n", hr);
    ok(iid.Data1 == 0x00000001, "Got %08x\n", iid.Data1);

    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(broken2W, &iid);
    ok(hr == CO_E_IIDSTRING, "got 0x%08x\n", hr);
    ok(iid.Data1 == 0x00000001, "Got %08x\n", iid.Data1);

    /* format is broken, but string length is okay */
    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(broken3W, &iid);
    ok(hr == CO_E_IIDSTRING, "got 0x%08x\n", hr);
    ok(iid.Data1 == 0xabababab, "Got %08x\n", iid.Data1);

    /* invalid string */
    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(wszNonExistent, &iid);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(iid.Data1 == 0xabababab, "Got %08x\n", iid.Data1);

    /* valid ProgID */
    memset(&iid, 0xab, sizeof(iid));
    hr = IIDFromString(stdfont, &iid);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(iid.Data1 == 0xabababab, "Got %08x\n", iid.Data1);
}